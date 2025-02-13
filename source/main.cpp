#include <iostream>
#include "ltype_vec.h"
#include "ltype_mat.h"
#include "ltype_quat.h"
#include "ltype_comp.h"

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    register_lua_vec<2, int>(L);
    register_lua_vec<3, int>(L);
    register_lua_vec<4, int>(L);

    register_lua_vec<2, unsigned int>(L);
    register_lua_vec<3, unsigned int>(L);
    register_lua_vec<4, unsigned int>(L);

    register_lua_vec<2, float>(L);
    register_lua_vec<3, float>(L);
    register_lua_vec<4, float>(L);

    register_lua_vec<2, double>(L);
    register_lua_vec<3, double>(L);
    register_lua_vec<4, double>(L);

    register_lua_mat<2, 2, int>(L);
    register_lua_mat<2, 3, int>(L);
    register_lua_mat<2, 4, int>(L);
    register_lua_mat<3, 2, int>(L);
    register_lua_mat<3, 3, int>(L);
    register_lua_mat<3, 4, int>(L);
    register_lua_mat<4, 2, int>(L);
    register_lua_mat<4, 3, int>(L);
    register_lua_mat<4, 4, int>(L);

    register_lua_mat<2, 2, unsigned int>(L);
    register_lua_mat<2, 3, unsigned int>(L);
    register_lua_mat<2, 4, unsigned int>(L);
    register_lua_mat<3, 2, unsigned int>(L);
    register_lua_mat<3, 3, unsigned int>(L);
    register_lua_mat<3, 4, unsigned int>(L);
    register_lua_mat<4, 2, unsigned int>(L);
    register_lua_mat<4, 3, unsigned int>(L);
    register_lua_mat<4, 4, unsigned int>(L);

    register_lua_mat<2, 2, float>(L);
    register_lua_mat<2, 3, float>(L);
    register_lua_mat<2, 4, float>(L);
    register_lua_mat<3, 2, float>(L);
    register_lua_mat<3, 3, float>(L);
    register_lua_mat<3, 4, float>(L);
    register_lua_mat<4, 2, float>(L);
    register_lua_mat<4, 3, float>(L);
    register_lua_mat<4, 4, float>(L);

    register_lua_mat<2, 2, double>(L);
    register_lua_mat<2, 3, double>(L);
    register_lua_mat<2, 4, double>(L);
    register_lua_mat<3, 2, double>(L);
    register_lua_mat<3, 3, double>(L);
    register_lua_mat<3, 4, double>(L);
    register_lua_mat<4, 2, double>(L);
    register_lua_mat<4, 3, double>(L);
    register_lua_mat<4, 4, double>(L);

    register_lua_quat<float>(L);
    register_lua_quat<double>(L);

    register_lua_comp<float>(L);
    register_lua_comp<double>(L);

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