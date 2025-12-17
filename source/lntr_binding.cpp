#include "lntr_binding.hpp"
#include <cstring>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
}

void* lua_ntr_new_data(lua_State* L, const ntr::nclass* type)
{
    uintptr_t type_size = static_cast<uintptr_t>(type->size());
    uintptr_t type_align = static_cast<uintptr_t>(type->align());
    void* userdata = lua_newuserdata(L, sizeof(ptrdiff_t) + type_size + type_align - 1);
    void* start = reinterpret_cast<char*>(userdata) + sizeof(ptrdiff_t);
    uintptr_t start_addr = reinterpret_cast<uintptr_t>(start);
    uintptr_t align_addr = (start_addr + type_align - 1) & ~(type_align - 1);
    *reinterpret_cast<ptrdiff_t*>(userdata) = align_addr - start_addr;
    return reinterpret_cast<void*>(align_addr);
}

void* lua_ntr_check_data(lua_State* L, int index, const ntr::nclass* type)
{
    void* userdata = luaL_checkudata(L, index, type->name().data());
    if (!lua_islightuserdata(L, index))
    {
        ptrdiff_t offset = *reinterpret_cast<ptrdiff_t*>(userdata);
        return reinterpret_cast<char*>(userdata) + sizeof(ptrdiff_t) + offset;
    }
    return userdata;
}

void lua_ntr_pushnobject(lua_State* L, ntr::nobject& object)
{
    if (object.type()->is_numeric())
    {
        if (object.type()->as_numeric()->numeric_kind() == ntr::nnumeric::enumeric::ebool)
        {
            lua_pushboolean(L, static_cast<bool>(ntr::nnumeric::get_value(object)));
        }
        else if (object.type()->as_numeric()->is_integral())
        {
            lua_pushinteger(L, static_cast<lua_Integer>(ntr::nnumeric::get_value(object)));
        }
        else
        {
            lua_pushnumber(L, ntr::nnumeric::get_value(object));
        }
    }
    else if (object.type() == ntr::nephren::get<std::string>())
    {
        lua_pushlstring(L, object.as<std::string>().c_str(), object.as<std::string>().size());
    }
    else if (object.type()->is_registered() && object.type()->is_class())
    {
        if (object.is_ref())
        {
            lua_pushlightuserdata(L, object.data());
        }
        else
        {
            void* userdata = lua_ntr_new_data(L, object.type()->as_class());
            if (object.type()->ops()->move_construct)
                object.type()->ops()->move_construct(userdata, object.data());
            else if (object.type()->ops()->copy_construct)
                object.type()->ops()->copy_construct(userdata, object.data());
            else
                luaL_error(L, "nephren type \"%s\" has no move or copy constructor", object.type()->name().data());
        }
        luaL_getmetatable(L, object.type()->name().data());
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "nephren type \"%s\" is not a registered type", object.type()->name().data());
    }
}

ntr::nobject lua_ntr_checknobject(lua_State* L, int index, const ntr::ntype* type)
{
    if (type->is_numeric())
    {
        ntr::nobject result = type->new_instance();
        double value = static_cast<double>(luaL_checknumber(L, index));
        ntr::nnumeric::set_value(result, value);
        return result;
    }
    else if (type == ntr::nephren::get<std::string>())
    {
        size_t len;
        const char* str = luaL_checklstring(L, index, &len);
        return type->move_instance(ntr::nwrapper(std::string(str, len)));
    }
    else if (type->is_registered() && type->is_class())
    {
        void* userdata = lua_ntr_check_data(L, index, type->as_class());
        return type->ref_instance(ntr::nwrapper(type, userdata));
    }
    else
    {
        luaL_error(L, "nephren type \"%s\" is not a registered type", type->name().data());
    }
    return type->new_instance();
}

int lua_ntr_new(lua_State* L, const ntr::nclass* type)
{
    std::string_view type_name = type->name();
    int arg_count = lua_gettop(L);
    if (arg_count > 1)
    {
        luaL_error(L, "nephren type \"%s\" create error : arguments size must be 0 or 1, but %d", type_name.data(),
                   arg_count);
        return 0;
    }

    void* userdata = lua_ntr_new_data(L, type);
    if (type->ops()->default_construct)
        type->ops()->default_construct(userdata);
    else
        memset(userdata, 0, type->size());

    if (arg_count == 1)
    {
        if (lua_istable(L, 1))
        {
            int index = lua_absindex(L, 1);
            lua_pushnil(L);
            while (lua_next(L, index) != 0)
            {
                size_t key_len;
                const char* key = lua_tolstring(L, -2, &key_len);
                if (const ntr::nproperty* property = type->get_property({ key, key_len }))
                {
                    ntr::nobject value = lua_ntr_checknobject(L, -1, property->property_type());
                    property->set(ntr::nwrapper(type, userdata), value.wrapper());
                }
                else
                {
                    luaL_error(L, "nephren type \"%s\" create error : arguments table has unknown property \"%s\"",
                               type_name.data(), key);
                }
                lua_pop(L, 1);
            }
        }
        else
        {
            luaL_error(L, "nephren type \"%s\" create error : arguments must be a table", type_name.data());
            return 0;
        }
    }

    luaL_getmetatable(L, type_name.data());
    lua_setmetatable(L, -2);

    return 1;
}

int lua_ntr_delete(lua_State* L, const ntr::nclass* type)
{
    void* userdata = lua_ntr_check_data(L, 1, type);
    if (type->ops()->destruct)
        type->ops()->destruct(userdata);
    return 0;
}

int lua_ntr_call(lua_State* L, const ntr::nclass* type, const std::string_view& function_name)
{
    std::string_view type_name = type->name();

    const ntr::nfunction* function = type->get_function(function_name);
    ntr::nvector<ntr::nobject> object_temps;
    object_temps.reserve(8);
    for (int i = 0; i < function->argument_types().size(); ++i)
    {
        const ntr::ntype* arg_type = function->argument_types()[i];
        object_temps.push_back(lua_ntr_checknobject(L, i + 1, arg_type));
    }

    ntr::nvector<ntr::nwrapper> args;
    args.reserve(object_temps.size());
    for (const auto& object : object_temps)
    {
        args.push_back(object.wrapper());
    }

    if (function->return_type() == ntr::nephren::get<void>())
    {
        function->call(args);
        return 0;
    }
    ntr::nobject result = function->call(args);
    lua_ntr_pushnobject(L, result);

    return 1;
}

void lua_ntr_set_function(lua_State* L, const ntr::nclass* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type regist function error : type is nullptr");

    /* | table | | metatable | */
    lua_pushlightuserdata(L, const_cast<ntr::nclass*>(type));
    for (auto it = type->functions().begin(); it != type->functions().end(); ++it)
    {
        std::string_view func_name = (*it).get()->name();
        lua_pushvalue(L, -1);
        lua_pushlstring(L, func_name.data(), func_name.size());
        auto call_lambda = [](lua_State* L)
        {
            const ntr::nclass* cls = reinterpret_cast<const ntr::nclass*>(lua_touserdata(L, lua_upvalueindex(1)));
            size_t func_name_len;
            const char* func_name = lua_tolstring(L, lua_upvalueindex(2), &func_name_len);
            return lua_ntr_call(L, cls, { func_name, func_name_len });
        };
        lua_pushcclosure(L, call_lambda, 2);
        if (!(*it).get()->is_static())
            lua_setfield(L, -3, func_name.data());
        else
            lua_setfield(L, -4, func_name.data());
    }
    lua_pop(L, 1);
}

void lua_ntr_set_property(lua_State* L, const ntr::nclass* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type regist property error : type is nullptr");

    /* | table | | metatable | */
    lua_pushlightuserdata(L, const_cast<ntr::nclass*>(type));
    auto index_lambda = [](lua_State* L)
    {
        const ntr::nclass* cls = reinterpret_cast<const ntr::nclass*>(lua_touserdata(L, lua_upvalueindex(1)));
        size_t key_len;
        const char* key = lua_tolstring(L, 2, &key_len);
        void* userdata = lua_ntr_check_data(L, 1, cls);
        if (const ntr::nproperty* property = cls->get_property({ key, key_len }))
        {
            ntr::nobject result = property->get(ntr::nwrapper(cls, userdata));
            lua_ntr_pushnobject(L, result);
        }
        else
        {
            lua_getmetatable(L, 1);
            lua_pushvalue(L, 2);
            lua_rawget(L, -2);
        }
        return 1;
    };
    auto new_index_lambda = [](lua_State* L)
    {
        const ntr::nclass* cls = reinterpret_cast<const ntr::nclass*>(lua_touserdata(L, lua_upvalueindex(1)));
        size_t key_len;
        const char* key = lua_tolstring(L, 2, &key_len);
        void* userdata = lua_ntr_check_data(L, 1, cls);
        if (const ntr::nproperty* property = cls->get_property({ key, key_len }))
        {
            ntr::nobject value = lua_ntr_checknobject(L, 3, property->property_type());
            property->set(ntr::nwrapper(cls, userdata), value.wrapper());
        }
        else
        {
            luaL_error(L, "nephren type \"%s\" set property \"%s\" error : has no property \"%s\"", cls->name().data(),
                       key);
        }
        return 0;
    };
    const luaL_Reg property_funcs[] = { { "__index", index_lambda },
                                        { "__newindex", new_index_lambda },
                                        { nullptr, nullptr } };
    luaL_setfuncs(L, property_funcs, 1);
}

void lua_ntr_set_typelife(lua_State* L, const ntr::nclass* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type regist metatable error : type is nullptr");

    /* | table | | metatable | */
    lua_pushlightuserdata(L, const_cast<ntr::nclass*>(type));
    lua_pushvalue(L, -1);
    auto gc_lambda = [](lua_State* L)
    {
        return lua_ntr_delete(L, reinterpret_cast<const ntr::nclass*>(lua_touserdata(L, lua_upvalueindex(1))));
    };
    lua_pushcclosure(L, gc_lambda, 1);
    lua_setfield(L, -3, "__gc");

    auto create_lambda = [](lua_State* L)
    {
        return lua_ntr_new(L, reinterpret_cast<const ntr::nclass*>(lua_touserdata(L, lua_upvalueindex(1))));
    };
    lua_pushcclosure(L, create_lambda, 1);
    lua_setfield(L, -3, "new");
}

void lua_ntr_new_type(lua_State* L, const std::string_view& type_name)
{
    auto type = ntr::nephren::get(type_name);
    if (!type->is_class())
        luaL_error(L, "nephren type regist error : type \"%s\" is not a class", type_name.data());
    lua_newtable(L);
    luaL_newmetatable(L, type->name().data());
    lua_ntr_set_typelife(L, type->as_class());
    lua_ntr_set_function(L, type->as_class());
    lua_ntr_set_property(L, type->as_class());
    lua_pop(L, 1);
}
