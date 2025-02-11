#include <iostream>
#include <string>
#include <vector>

extern "C" {
    #include "../lua/lua.h"
    #include "../lua/lualib.h"
    #include "../lua/lauxlib.h"
}

// 向量类
class fvec {
public:
    std::vector<double> data;
    
    fvec(const std::vector<double>& v) : data(v) {}
    
    fvec operator+(const fvec& other) const {
        std::vector<double> result;
        size_t size = std::min(data.size(), other.data.size());
        result.reserve(size);
        for (size_t i = 0; i < size; ++i) {
            result.push_back(data[i] + other.data[i]);
        }
        return fvec(result);
    }
};

// 创建向量的辅助函数
static fvec* check_fvec(lua_State* L, int index) {
    return (fvec*)luaL_checkudata(L, index, "fvec");
}

// 向量元表的__gc方法
static int fvec_gc(lua_State* L) {
    fvec* v = check_fvec(L, 1);
    v->~fvec();
    return 0;
}

// 创建新向量的Lua函数
static int create_fvec(lua_State* L) {
    int n = lua_gettop(L);  // 获取参数数量
    std::vector<double> values;
    values.reserve(n);
    
    for (int i = 1; i <= n; ++i) {
        values.push_back(luaL_checknumber(L, i));
    }
    
    // 在Lua中创建用户数据
    void* data = lua_newuserdata(L, sizeof(fvec));
    new(data) fvec(values);  // placement new
    
    // 设置元表
    luaL_getmetatable(L, "fvec");
    lua_setmetatable(L, -2);
    
    return 1;
}

// 向量相加的Lua方法
static int fvec_add(lua_State* L) {
    fvec* v1 = check_fvec(L, 1);
    fvec* v2 = check_fvec(L, 2);
    
    void* data = lua_newuserdata(L, sizeof(fvec));
    new(data) fvec(*v1 + *v2);
    
    luaL_getmetatable(L, "fvec");
    lua_setmetatable(L, -2);
    
    return 1;
}

// 打印向量的方法
static int fvec_tostring(lua_State* L) {
    fvec* v = check_fvec(L, 1);
    std::string result = "fvec{";
    for (size_t i = 0; i < v->data.size(); ++i) {
        if (i > 0) result += ", ";
        result += std::to_string(v->data[i]);
    }
    result += "}";
    lua_pushstring(L, result.c_str());
    return 1;
}

// C++ 函数，将被导出到 Lua
static int cpp_add(lua_State* L) {
    double a = luaL_checknumber(L, 1);  // 获取第一个参数
    double b = luaL_checknumber(L, 2);  // 获取第二个参数
    
    lua_pushnumber(L, a + b);  // 将结果压入栈
    return 1;  // 返回值个数
}

int main() {
    // 创建 Lua 状态
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);  // 加载标准库

    // 创建fvec的元表
    luaL_newmetatable(L, "fvec");
    
    // 设置元表的方法
    lua_pushstring(L, "__gc");
    lua_pushcfunction(L, fvec_gc);
    lua_settable(L, -3);
    
    lua_pushstring(L, "__add");
    lua_pushcfunction(L, fvec_add);
    lua_settable(L, -3);
    
    lua_pushstring(L, "__tostring");
    lua_pushcfunction(L, fvec_tostring);
    lua_settable(L, -3);

    // 注册 C++ 函数到 Lua
    lua_pushcfunction(L, cpp_add);
    lua_setglobal(L, "cpp_add");
    
    // 注册创建向量的函数
    lua_pushcfunction(L, create_fvec);
    lua_setglobal(L, "fvec");

    // 执行 Lua 脚本文件
    if (luaL_dofile(L, "scripts/test.lua") != LUA_OK) {
        std::cerr << "Lua 执行错误: " << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }

    // 清理
    lua_close(L);
    return 0;
} 