#include <iostream>
using namespace std;

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

    //设置元表
    luaL_getmetatable(L, "student_mt");
    lua_setmetatable(L, -2);

    return 1;
}

static int GetId(lua_State *L)
{
    Student *p_student = (Student*)luaL_checkudata(L, 1, "student_mt");
    lua_pushnumber(L, p_student->id);

    return 1;
}

static int GetName(lua_State *L)
{
    Student *p_student = (Student*)luaL_checkudata(L, 1, "student_mt");
    lua_pushstring(L, p_student->name);

    return 1;
}

static int SetName(lua_State *L)
{
    Student *p_student = (Student*)luaL_checkudata(L, 1, "student_mt");

    const char *name = luaL_checkstring(L, 2);
    luaL_argcheck(L, name != nullptr && name != "", 2, "SetName:error para name");

    p_student->name = const_cast<char*>(name);
}

static const struct luaL_Reg student_lib[] = 
{
    {"NewStudent", NewStudent}, 
    {nullptr, nullptr}
};

static const struct luaL_Reg student_lib_meta[] = 
{
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
    
    //3. 创建一个元表
    luaL_newmetatable(L, "student_mt");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    //4.注册一系列函数
    luaL_register(L, nullptr, student_lib_meta);
    luaL_register(L, "student_lib", student_lib);

    //5.加载并运行Lua文件
    if (luaL_dofile(L, "lua_five.lua"))
    {
        cout << "luaL_dofile fail" << endl;
        return 1;
    }

    //6.关闭state
    lua_close(L);
    return 0;
}