#include <iostream>
#include "lua_type_vec.h"

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_lua_vec<2, float>(L);
    register_lua_vec<3, float>(L);
    register_lua_vec<4, float>(L);

    if (argc > 1)
    {
        if (luaL_dofile(L, argv[1]) != LUA_OK)
        {
            std::cerr << "Lua Runtime Error: " << lua_tostring(L, -1) << std::endl;
        }
    }

    lua_close(L);

    return 0;
}