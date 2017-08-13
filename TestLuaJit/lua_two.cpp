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

    //2.加载所有lua库到lua状态机，否则lua代码中的string.fromat等函数不能用
    luaL_openlibs(L);

    //3.加载并运行Lua文件，相当于luaL_loadfile(L, "lua_two.lua")和lua_pcall(L, 0, 0, 0)
    if (luaL_dofile(L, "lua_two.lua"))
    {
        cout << "luaL_dofile fail" << endl;
        return 1;
    }

    //4.读取变量，注意lua_getglobal不能读取local变量
    lua_getglobal(L, "str");
    cout << "str=" << lua_tostring(L, -1) << endl;

    //5.读取table，状态机是个栈，先进后出
    lua_getglobal(L, "tb");
    lua_getfield(L, -1, "name");
    lua_getfield(L, -2, "id");
    cout << "tb:name=" << lua_tostring(L, -2) << ", id=" << lua_tonumber(L, -1) << endl;

    //6.读取函数
    lua_getglobal(L, "get_str");            // 获取函数，压入栈中
    lua_pushnumber(L, 10);                  // 压入第一个参数
    lua_pushstring(L, "xx");                // 压入第二个参数 
    if (lua_pcall(L, 2, 1, 0))              // 调用函数，调用完成以后，会将返回值压入栈中，2表示参数个数，1表示返回结果个数。
    {
        cout << lua_tostring(L, -1) << endl;
        lua_close(L);
        return 1;
    }
    if (lua_isstring(L, -1))                // 取值输出
    {
        cout << "result is " << lua_tostring(L, -1) << endl;
    }

    //至此，栈中的情况是：
    //=================== 栈顶 ===================
    //  索引  类型      值
    //   5   string     result is 10+xx
    //   4   int        1
    //   3   string：   xx
    //   2   table:     tbl
    //   1   string:    I am so cool!
    //=================== 栈底 ===================
    //7.打印lua栈中的值
    cout << "lua_state:length=" << lua_gettop(L) << endl;
    cout << "index[-1]=" << lua_tostring(L, -1);
    cout << ", index[-2]=" << lua_tonumber(L, -2);
    cout << ", index[-3]=" << lua_tostring(L, -3);
    cout << ", index[-4]=" << lua_istable(L, -4);
    cout << ", index[-5]=" << lua_tostring(L, -5);
    cout << endl;
    cout << "index[5]=" << lua_tostring(L, 5);
    cout << ", index[4]=" << lua_tonumber(L, 4);
    cout << ", index[3]=" << lua_tostring(L, 3);
    cout << ", index[2]=" << lua_istable(L, 2);
    cout << ", index[1]=" << lua_tostring(L, 1);
    cout << endl;

    //8.更改table中的值
    lua_pushstring(L, "n");
    lua_pushnumber(L, 2);
    lua_setfield(L, 2, "id");
    lua_setfield(L, 2, "name");
    lua_getglobal(L, "tb");// 读取
    lua_getfield(L, -1, "name");
    lua_getfield(L, -2, "id");
    cout << "tb:name=" << lua_tostring(L, -2) << ", id=" << lua_tonumber(L, -1) << endl;

    //9.从栈顶弹出三个值
    lua_pop(L, 3);

    //10.打印lua栈中的值
    cout << "lua_state:length=" << lua_gettop(L) << endl;
    cout << "index[-1]=" << lua_tostring(L, -1);
    cout << ", index[-2]=" << lua_tonumber(L, -2);
    cout << ", index[-3]=" << lua_tostring(L, -3);
    cout << ", index[-4]=" << lua_istable(L, -4);
    cout << ", index[-5]=" << lua_tostring(L, -5);
    cout << endl;
    cout << "index[5]=" << lua_tostring(L, 5);
    cout << ", index[4]=" << lua_tonumber(L, 4);
    cout << ", index[3]=" << lua_tostring(L, 3);
    cout << ", index[2]=" << lua_istable(L, 2);
    cout << ", index[1]=" << lua_tostring(L, 1);
    cout << endl;
    
    //11.关闭state
    lua_close(L);
    return 0;
}