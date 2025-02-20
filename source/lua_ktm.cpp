//  MIT License
//
//  Copyright (c) 2025 有个小小杜
//
//  Created by 有个小小杜
//

#include <iostream>
#include "lvec.h"
#include "lmat.h"
#include "lquat.h"
#include "lcomp.h"

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_lvec<2>(L);
    register_lvec<3>(L);
    register_lvec<4>(L);

    register_lmat<2, 2>(L);
    register_lmat<2, 3>(L);
    register_lmat<2, 4>(L);
    register_lmat<3, 2>(L);
    register_lmat<3, 3>(L);
    register_lmat<3, 4>(L);
    register_lmat<4, 2>(L);
    register_lmat<4, 3>(L);
    register_lmat<4, 4>(L);

    register_lquat(L);
    register_lcomp(L);

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