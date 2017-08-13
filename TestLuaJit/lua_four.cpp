#include <iostream>
#include <string>
using namespace std;

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

//待Lua调用的C注册函数
static int fun(lua_State* L)
{
    //检查栈中的参数是否合法
    int para_one = luaL_checknumber(L, 1);
    std::string para_two = luaL_checkstring(L, 2);

    //将函数的结果压入栈中。
    lua_pushnumber(L, para_one);
    lua_pushstring(L, para_two.c_str());

    //返回值为该C函数的返回值数量，即压入栈中的返回值数量。
    return 2;
}
static int split(lua_State *L)
{
    std::string str_src = luaL_checkstring(L, 1);
    std::string str_sep = luaL_checkstring(L, 2);

    // 创建table，压入栈，索引为-1
    lua_newtable(L);
    int index = 1;

    if (str_sep.length() != 1)
    {
        std::string error_str = "seq must be a char.";
        lua_pushstring(L, error_str.c_str());
        lua_rawseti(L, -2, index++);
        return 1;
    }

    std::string str = "";
    for (int i = 0; i < str_src.length(); ++i)
    {
        if (str_sep.find(str_src[i]) != std::string::npos)
        {
            // 将结果压入栈，索引为-1，此时栈上的table索引为-2
            lua_pushstring(L, str.c_str());
            // 索引-2处为一个table，将table的key为index++处的value设为栈顶的值(即索引为-1处的值)
            // 并将栈顶的值弹出
            lua_rawseti(L, -2, index++);
            str = "";
        }
        else
        {
            str += str_src[i];
        }
    }
    lua_pushstring(L, str.c_str());
    lua_rawseti(L, -2, index);

    return 1;
}

int main()
{
    //1.创建Lua状态机
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return 1;
    }

    //2.加载所有lua库到lua状态机，否则lua代码中的string.fromat等函数不能用
    luaL_openlibs(L);

    //3.将指定的函数注册为Lua的全局函数变量
    lua_register(L, "fun", fun);
    lua_register(L, "split", split);

    //4.加载并运行Lua文件
    if (luaL_dofile(L, "lua_four.lua"))
    {
        cout << "luaL_dofile fail" << endl;
        return 1;
    }

    //5.关闭state
    lua_close(L);
    return 0;
}