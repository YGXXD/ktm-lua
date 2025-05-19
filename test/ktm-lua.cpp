//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include <iostream>
#include "lktmlib.hpp"

extern "C"
{
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, luaopen_ktm);
    lua_call(L, 0, 1);
    lua_setglobal(L, "ktm");

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