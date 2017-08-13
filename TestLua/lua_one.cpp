#include <iostream>  
#include <string.h>  
using namespace std;  

extern "C"  
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

int main()
{
    //1.创建一个state
    lua_State *L = luaL_newstate();

    //2.入栈操作
    lua_pushstring(L, "I am so cool!");
    lua_pushnumber(L, 20);
   
    //3.取值操作
    if (lua_isstring(L, 1))
    {
        cout << lua_tostring(L, 1) << endl;
    }  
    if(lua_isnumber(L, 2))
    {  
        cout << lua_tonumber(L, 2) << endl;  
    }  

    //4.关闭state  
    lua_close(L);
    return 0;
}
