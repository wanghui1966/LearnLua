#include <iostream>
using namespace std;
//http://www.jellythink.com/archives/587
extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

static int index = 0;

typedef struct Student
{
    int id;
    char *name; //此处换成std::string总是不行，好奇怪？
}Student;

static int NewStudent(lua_State *L)
{
    Student *p_student = nullptr;
    p_student = (Student*)lua_newuserdata(L, sizeof(Student));

    p_student->id = ++index;
    //如果此处不设置默认值，极有可能导致堆栈破坏
    p_student->name = "default name";

    return 1;
}

static int GetId(lua_State *L)
{
    Student *p_student = (Student*)lua_touserdata(L, 1);
    luaL_argcheck(L, p_student != nullptr, 1, "GetId:error para Student");
    lua_pushnumber(L, p_student->id);

    return 1;
}

static int GetName(lua_State *L)
{
    Student *p_student = (Student*)lua_touserdata(L, 1);
    luaL_argcheck(L, p_student != nullptr, 1, "GetName:error para Student");
    lua_pushstring(L, p_student->name);

    return 1;
}

static int SetName(lua_State *L)
{
    Student *p_student = (Student*)lua_touserdata(L, 1);
    luaL_argcheck(L, p_student != nullptr, 1, "SetName:error para Student");

    const char *name = luaL_checkstring(L, 2);
    luaL_argcheck(L, name != nullptr && name != "", 2, "SetName:error para name");

    p_student->name = const_cast<char*>(name);
}

static const struct luaL_Reg student_lib[] = 
{
    {"NewStudent", NewStudent}, 
    {"GetId", GetId},
    {"GetName", GetName}, 
    {"SetName", SetName},
    {nullptr, nullptr}
};

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

    //3.注册一系列函数
    luaL_register(L, "student_lib", student_lib);

    //4.加载并运行Lua文件
    if (luaL_dofile(L, "lua_five.lua"))
    {
        cout << "luaL_dofile fail" << endl;
        return 1;
    }

    //5.关闭state
    lua_close(L);
    return 0;
}