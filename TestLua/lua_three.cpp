#include <iostream>
#include <string>
using namespace std;

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int main()
{
    //1.创建Lua状态机
    lua_State *L = luaL_newstate();
    if (L == NULL)
    {
        return 1;
    }

    //2.创建table
    lua_newtable(L);

    //3.往table中插值
    lua_pushnumber(L, 20);
    lua_setfield(L, -2, "w");
    lua_pushnumber(L, 30);
    lua_setfield(L, -2, "h");

    //4.设置为global
    lua_setglobal(L, "tb");

	//5.取table中的值
    lua_getglobal(L, "tb");
	lua_getfield(L, -1, "w");
	lua_getfield(L, -2, "h");

    //至此，栈中的情况是：
    //=================== 栈顶 ===================
    //  索引  类型      值
    //   3   string：   "h"
    //   2   string：:  "w"
    //   1   table:     tb
    //=================== 栈底 ===================
    //6.打印lua栈中的值
    cout << "lua_state:length=" << lua_gettop(L) << endl;
    cout << "index[-1]=" << lua_tonumber(L, -1);
    cout << ", index[-2]=" << lua_tonumber(L, -2);
    cout << ", index[-3]=" << lua_istable(L, -3);
    cout << endl;
    cout << "index[3]=" << lua_tonumber(L, 3);
    cout << ", index[2]=" << lua_tonumber(L, 2);
    cout << ", index[1]=" << lua_istable(L, 1);
    cout << endl;

    //7.关闭state
    lua_close(L);
    return 0;
}
