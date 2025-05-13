#include "lua_ntr_api.hpp"
#include "ntr/inc/nephren.hpp"

void lua_pushnobject(lua_State* L, ntr::nobject& object)
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
    else if (object.type()->is_registered())
    {
        if (object.kind() == ntr::nobject::eobject::eref)
        {
            lua_pushlightuserdata(L, object.data());
        }
        else
        {
            void* realdata = _ntr_align_alloc(object.type()->size(), object.type()->align());
            void** userdata = reinterpret_cast<void**>(lua_newuserdata(L, sizeof(void*)));
            *userdata = realdata;
            if (object.type()->ops()->move_construct)
                object.type()->ops()->move_construct(realdata, object.data());
            else if (object.type()->ops()->copy_construct)
                object.type()->ops()->copy_construct(realdata, object.data());
            else
                luaL_error(L, "nephren type %s has no move or copy constructor", object.type()->name().data());
        }
        luaL_getmetatable(L, object.type()->name().data());
        lua_setmetatable(L, -2);
    }
    else
    {
        luaL_error(L, "nephren type %s is not a registered type", object.type()->name().data());
    }
}

ntr::nobject lua_checknobject(lua_State* L, int index, const ntr::ntype* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type is nullptr, cannot check nobject");

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
        return type->new_instance_rv(ntr::nwrapper(std::string(str, len)));
    }
    else
    {
        void* realdata = *reinterpret_cast<void**>(luaL_checkudata(L, index, type->name().data()));
        return type->new_reference(ntr::nwrapper(type, realdata));
    }
}

int lua_ntr_new(lua_State* L, const std::string_view& type_name)
{
    int arg_count = lua_gettop(L) - 1;
    if (arg_count != 0)
    {
        luaL_error(L, "nephren type %s new arguments size must be 0, but %d", type_name.data(), arg_count);
        return 0;
    }

    auto type = ntr::nephren::get(type_name);
    void* realdata = _ntr_align_alloc(type->size(), type->align());
    if (type->ops()->default_construct)
        type->ops()->default_construct(realdata);
    else
        memset(realdata, 0, type->size());
    void** userdata = reinterpret_cast<void**>(lua_newuserdata(L, sizeof(void*)));
    *userdata = realdata;

    luaL_getmetatable(L, type_name.data());
    lua_setmetatable(L, -2);

    return 1;
}

int lua_ntr_delete(lua_State* L, const std::string_view& type_name)
{
    void* realdata = *reinterpret_cast<void**>(luaL_checkudata(L, 1, type_name.data()));
    _ntr_align_free(realdata);
    return 0;
}

int lua_ntr_call(lua_State* L, const std::string_view& type_name, const std::string_view& function_name)
{
    const ntr::ntype* type = ntr::nephren::get(type_name);
    if (type == nullptr)
    {
        luaL_error(L, "nephren type %s not found", type_name.data());
        return 0;
    }
    const ntr::nclass* cls = type->as_class();
    if (cls == nullptr)
    {
        luaL_error(L, "nephren type %s is not a class", type_name.data());
        return 0;
    }

    const ntr::nfunction* function = cls->get_function(function_name);
    std::vector<ntr::nobject> object_temps;
    object_temps.reserve(8);
    for (int i = 0; i < function->argument_types().size(); ++i)
    {
        const ntr::ntype* arg_type = function->argument_types()[i];
        object_temps.push_back(lua_checknobject(L, i + 1, arg_type));
    }

    std::vector<ntr::nwrapper> args;
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
    lua_pushnobject(L, result);

    return 1;
}

void lua_ntr_register_function(lua_State* L, const ntr::nclass* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type is nullptr, cannot register function");

    luaL_getmetatable(L, type->name().data());
    for (auto it = type->function_begin(); it != type->function_end(); ++it)
    {
        lua_pushlstring(L, type->name().data(), type->name().size());
        lua_pushlstring(L, (*it).get()->name().data(), (*it).get()->name().size());
        auto call_lambda = [](lua_State* L)
        {
            size_t type_name_len;
            const char* type_name = lua_tolstring(L, lua_upvalueindex(1), &type_name_len);
            size_t func_name_len;
            const char* func_name = lua_tolstring(L, lua_upvalueindex(2), &func_name_len);
            return lua_ntr_call(L, { type_name, type_name_len }, { func_name, func_name_len });
        };
        lua_pushcclosure(L, call_lambda, 2);
        lua_setfield(L, -2, (*it).get()->name().data());
    }
    lua_pop(L, 1);
}

void lua_ntr_register_property(lua_State* L, const ntr::nclass* type)
{
    if (type == nullptr)
        luaL_error(L, "nephren type is nullptr, cannot register property");

    luaL_getmetatable(L, type->name().data());
    lua_pushlstring(L, type->name().data(), type->name().size());
    auto index_lambda = [](lua_State* L)
    {
        size_t type_name_len;
        const char* type_name = lua_tolstring(L, lua_upvalueindex(1), &type_name_len);
        auto cls = ntr::nephren::get(type_name)->as_class();
        size_t key_len;
        const char* key = lua_tolstring(L, 2, &key_len);
        void* realdata = *reinterpret_cast<void**>(luaL_checkudata(L, 1, type_name));
        if (const ntr::nproperty* property = cls->get_property({ key, key_len }))
        {
            ntr::nobject result = property->get(ntr::nwrapper(cls, realdata));
            lua_pushnobject(L, result);
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
        size_t type_name_len;
        const char* type_name = lua_tolstring(L, lua_upvalueindex(1), &type_name_len);
        auto cls = ntr::nephren::get(type_name)->as_class();
        size_t key_len;
        const char* key = lua_tolstring(L, 2, &key_len);
        void* realdata = *reinterpret_cast<void**>(luaL_checkudata(L, 1, type_name));
        if (const ntr::nproperty* property = cls->get_property({ key, key_len }))
        {
            ntr::nobject value = lua_checknobject(L, 3, property->property_type());
            property->set(ntr::nwrapper(cls, realdata), value.wrapper());
        }
        else
        {
            luaL_error(L, "nephren type %s has no property %s", type_name, key);
        }
        return 0;
    };
    const luaL_Reg property_funcs[] = { { "__index", index_lambda },
                                        { "__newindex", new_index_lambda },
                                        { nullptr, nullptr } };
    luaL_setfuncs(L, property_funcs, 1);

    lua_pop(L, 1);
}

void lua_ntr_register(lua_State* L, const std::string_view& type_name)
{
    auto type = ntr::nephren::get(type_name);
    luaL_newmetatable(L, type->name().data());

    lua_pushlstring(L, type->name().data(), type->name().size());
    auto gc_lambda = [](lua_State* L)
    {
        size_t type_name_len;
        const char* type_name = lua_tolstring(L, lua_upvalueindex(1), &type_name_len);
        return lua_ntr_delete(L, { type_name, type_name_len });
    };
    lua_pushcclosure(L, gc_lambda, 1);
    lua_setfield(L, -2, "__gc");

    lua_newtable(L);
    lua_pushlstring(L, type->name().data(), type->name().size());
    auto create_lambda = [](lua_State* L)
    {
        size_t type_name_len;
        const char* type_name = lua_tolstring(L, lua_upvalueindex(1), &type_name_len);
        return lua_ntr_new(L, { type_name, type_name_len });
    };
    lua_pushcclosure(L, create_lambda, 1);
    lua_setfield(L, -2, "__call");

    lua_setmetatable(L, -2);
    lua_setglobal(L, type->name().data());

    lua_ntr_register_function(L, type->as_class());
    lua_ntr_register_property(L, type->as_class());
}