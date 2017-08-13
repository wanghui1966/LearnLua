#ifndef LUA_TINKER_PACKAGE_H
#define LUA_TINKER_PACKAGE_H

#include <string>
#include <stdint.h>

#include "lua_tinker.h"

/********************************************************/
/* C++类，封装了lua_tinker接口                          */
/********************************************************/
class LuaTinkerPackage
{
public:
    LuaTinkerPackage() : state(nullptr)
    {

    }

    virtual ~LuaTinkerPackage()
    {
        if (state)
        {
            lua_close(state);
        }
        state = nullptr;
    }

public:
    lua_State* get_lua_state()
    {
        return state;
    }

    bool init(const char *file_name)
    {
        if (state)
        {
            return false;
        }

        state = luaL_newstate();
        if (state == nullptr)
        {
            return false;
        }

        luaL_openlibs(state);
        lua_tinker::init(state);
        return dofile(file_name);
    }

public:
    bool dofile(const char *file_name)
    {
        return lua_tinker::dofile(state, file_name);
    }

    template<class T>
    void setglobal(const char *name, T obj)
    {
        lua_tinker::setglobal<T>(state, name, obj);
    }

    template<class T>
    T getglobal(const char *name)
    {
        return lua_tinker::getglobal<T>(state, name);
    }

    // 注册全局函数
    template<class T>
    void reg_func(const char *func_name, T func)
    {
        lua_tinker::def<T>(state, func_name, func);
    }

    // 注册全局函数，特化，返回值需要自行压栈
    void reg_func(const char *func_name, lua_CFunction func)
    {
        lua_register(state, func_name, func);
    }

    // 注册类
    template<class T>
    void reg_class(const char *class_name)
    {
        lua_tinker::class_add<T>(state, class_name);
    }

    // 注册类构造函数
    template<class T>
    void reg_class_con_func()
    {
        lua_tinker::class_con<T>(state, &(lua_tinker::constructor<T>));
    }

    // 注册类成员函数
    template<class T, class F>
    void reg_class_func(const char *class_name, F func)
    {
        lua_tinker::class_def<T>(state, class_name, func);
    }

    // 注册类变量
    template<class T, class BASE, class VAR>
    void reg_class_var(const char *class_name, VAR BASE::*var)
    {
        lua_tinker::class_mem<T>(state, class_name, var);
    }

public:
    // 调用lua函数接口
    template<class T>
    T call_lua(const char *func_name)
    {
        return lua_tinker::call<T>(state, func_name);
    }

    template<class T, class T1>
    T call_lua(const char *func_name, const T1 &t1)
    {
        return lua_tinker::call<T, T1>(state, func_name, t1);
    }

    template<class T, class T1, class T2>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2)
    {
        return lua_tinker::call<T, T1, T2>(state, func_name, t1, t2);
    }

    template<class T, class T1, class T2, class T3>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3)
    {
        return lua_tinker::call<T, T1, T2, T3>(state, func_name, t1, t2, t3);
    }

    template<class T, class T1, class T2, class T3, class T4>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4)
    {
        return lua_tinker::call<T, T1, T2, T3, T4>(state, func_name, t1, t2, t3, t4);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5)
    {
        return lua_tinker::call<T, T1, T2, T3, T4, T5>(state, func_name, t1, t2, t3, t4, t5);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6)
    {
        return lua_tinker::call<T, T1, T2, T3, T4, T5, T6>(state, func_name, t1, t2, t3, t4, t5, t6);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6, const T7 &t7)
    {
        return lua_tinker::call<T, T1, T2, T3, T4, T5, T6, T7>(state, func_name, t1, t2, t3, t4, t5, t6, t7);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    T call_lua(const char *func_name, const T1 &t1, const T2 &t2, const T3 &t3, const T4 &t4, const T5 &t5, const T6 &t6, const T7 &t7, const T8 &t8)
    {
        return lua_tinker::call<T, T1, T2, T3, T4, T5, T6, T7, T8>(state, func_name, t1, t2, t3, t4, t5, t6, t7, t8);
    }

protected:
    lua_State *state;                               // lua状态机
};

enum LuaValueType
{
    NULL_TYPE = 0,
    INT32_TYPE,
    UINT32_TYPE,
    INT64_TYPE,
    UINT64_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    PTR_TYPE,
};

typedef struct LuaValue
{
    int type;
    union
    {
        int32_t                     int32_value;
        uint32_t                    uint32_value;
        int64_t                     int64_value;
        uint64_t                    uint64_value;
        double                      double_value;
        char                        string_value[256];
        void                        *ptr_value;
    }value;

    LuaValue()
    {
        type = NULL_TYPE;
    }

    LuaValue(int32_t data)
    {
        type = INT32_TYPE;
        value.int32_value = data;
    }

    LuaValue(uint32_t data)
    {
        type = UINT32_TYPE;
        value.uint32_value = data;
    }

    LuaValue(int64_t data)
    {
        type = INT64_TYPE;
        value.int64_value = data;
    }

    LuaValue(uint64_t data)
    {
        type = UINT64_TYPE;
        value.uint64_value = data;
    }

    LuaValue(double data)
    {
        type = DOUBLE_TYPE;
        value.double_value = data;
    }

    LuaValue(const std::string &data)
    {
        type = STRING_TYPE;
        memset(value.string_value, 0, sizeof(value.string_value));
        memcpy(value.string_value, data.c_str(), data.length());
    }
    LuaValue(const char *data, int len)
    {
        type = STRING_TYPE;
        memset(value.string_value, 0, sizeof(value.string_value));
        memcpy(value.string_value, data, len);
    }

    LuaValue(void *data)
    {
        type = PTR_TYPE;
        value.ptr_value = data;
    }
}LuaValue;

#endif