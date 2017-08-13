#ifndef TOLUA_PACKAGE_H
#define TOLUA_PACKAGE_H

#include <iostream>
#include <string>
#include <cstring>
#include <cxxabi.h>

#include "tolua++.h"
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
};

namespace ToluaPackage
{
    // 栈最大层次
    static const int STACK_MAX_LEVEL = 100;
    // 栈最多记录的变量数
    static const int STACK_MAX_VALUE_NUM = 100;

    static const char* value_to_string(lua_State *state, int idx)
    {
        static char s[1024] = {0};
        switch (lua_type(state, idx))
        {
        case LUA_TNUMBER:
        case LUA_TSTRING:
            return lua_tostring(state, idx);
        case LUA_TBOOLEAN:
            return lua_toboolean(state, idx) ? "true" : "false";
        case LUA_TNIL:
            return "nil";
        case LUA_TFUNCTION:
        {
            lua_Debug stack;
            lua_pushvalue(state, idx);
            lua_getinfo(state, ">S", &stack);
            if (!stack.name)
            {
                stack.name = "?";
            }
            snprintf(s, sizeof(s), "function: %s.%d", stack.source, stack.linedefined);
            return s;
        }
        default:
        {
            snprintf(s, sizeof(s), "%s: %p", luaL_typename(state, idx), lua_topointer(state, idx));
            return s;
        }
        }
    }

    static void trace_upvalue(lua_State *state, lua_Debug &stack)
    {
        for (int i = 1; i <= STACK_MAX_VALUE_NUM; ++i)
        {
            lua_getinfo(state, "f", &stack);
            const char *name = lua_getupvalue(state, -1, i);
            lua_remove(state, -2);

            if (!name)
            {
                break;
            }

            if (i == 1)
            {
                std::cout << "******up value" << std::endl;
            }

            const char *value = value_to_string(state, -1);
            char kv_pair[1024] = {0};
            snprintf(kv_pair, sizeof(kv_pair), "%s : %s", name, value);
            std::cout << kv_pair << std::endl;
            lua_pop(state, 1);
        }
    }

    static void trace_local_value(lua_State *state, lua_Debug &stack)
    {
        for (int i = 1; i <= STACK_MAX_VALUE_NUM; ++i)
        {
            const char *name = lua_getlocal(state, &stack, i);
            if (!name)
            {
                break;
            }

            if (i == 1)
            {
                std::cout << "******local value" << std::endl;
            }

            const char *value = value_to_string(state, -1);
            char kv_pair[1024] = {0};
            snprintf(kv_pair, sizeof(kv_pair), "%s : %s", name, value);
            std::cout << kv_pair << std::endl;
            lua_pop(state, 1);
        }
    }

    static bool trace_module_and_function(lua_State *state, lua_Debug &stack)
    {
        lua_getinfo(state, "Sln", &stack);
        // 跳过tail call
        if (stack.what && strcmp(stack.what, "tail") == 0)
        {
            return false;
        }

        if (!stack.name)
        {
            stack.name = "?";
        }

        char func_info[1024] = {0};
        snprintf(func_info, sizeof(func_info), "%s.%d!%s:%d.\n",
            stack.source, stack.linedefined, stack.name, stack.currentline);
        std::cout << func_info;

        return true;
    }

    extern int lua_error_handler(lua_State *state)
    {
        std::cout << "======lua exception start:" << lua_tostring(state, -1) << std::endl;

        for (int i = 0; i <= STACK_MAX_LEVEL; ++i)
        {
            lua_Debug stack = { 0 };
            if (!lua_getstack(state, i, &stack))
            {
                break;
            }
            if (!trace_module_and_function(state, stack))
            {
                continue;
            }
            trace_upvalue(state, stack);
            trace_local_value(state, stack);
        }

        std::cout << "======lua exception end:" << std::endl;

        return 0;
    }

    template<typename T>
    inline std::string& get_class_name(T* obj)
    {
        static std::string class_name;
        if (class_name.empty())
        {
            int status;
            char *real_name = abi::__cxa_demangle(typeid(*obj).name(), 0, 0, &status);
            if (!real_name)
            {
                std::cout << "get_class_name error:class_name=" << typeid(*obj).name() << std::endl;
                return class_name;
            }
            class_name = real_name;
            free(real_name);
        }
        return class_name;
    }

    // push函数
    template<class T>
    inline void push(lua_State *state, T *obj)
    {
        tolua_pushusertype(state, obj, get_class_name<T>(obj).c_str());
    }

    inline void push(lua_State *state, char ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, unsigned char ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, short ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, unsigned short ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, int ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, unsigned int ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, float ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, double ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, char* ret)
    {
        lua_pushstring(state, ret);
    }

    inline void push(lua_State *state, const char* ret)
    {
        lua_pushstring(state, ret);
    }

    inline void push(lua_State *state, bool ret)
    {
        lua_pushboolean(state, ret);
    }

#if defined(__X86_64__) || defined(__X86_64) || defined(__amd_64) || defined(__amd_64__)
    inline void push(lua_State *state, long ret)
    {
        *(long*)lua_newuserdata(state, sizeof(long)) = ret;
        lua_gettable(state, "__s64");
        lua_setmetatable(state, -2);
    }

    inline void push(lua_State *state, unsigned long ret)
    {
        *(unsigned long*)lua_newuserdata(state, sizeof(unsigned long)) = ret;
        lua_gettable(state, "__u64");
        lua_setmetatable(state, -2);
    }
#else
    inline void push(lua_State *state, long ret)
    {
        lua_pushnumber(state, ret);
    }

    inline void push(lua_State *state, unsigned long ret)
    {
        lua_pushnumber(state, ret);
    }
#endif

    inline void push(lua_State *state, long long ret)
    {
        *(long long*)lua_newuserdata(state, sizeof(long long)) = ret;
        lua_getglobal(state, "__s64");
        lua_setmetatable(state, -2);
    }

    inline void push(lua_State *state, unsigned long long ret)
    {
        *(unsigned long long*)lua_newuserdata(state, sizeof(unsigned long long)) = ret;
        lua_getglobal(state, "__u64");
        lua_setmetatable(state, -2);
    }

    inline void push(lua_State *state, std::string *ret)
    {
        lua_pushlstring(state, ret->c_str(), ret->size());
    }

    inline void push(lua_State *state, const std::string *ret)
    {
        lua_pushlstring(state, ret->c_str(), ret->size());
    }

    inline void push(lua_State *state, const std::string &ret)
    {
        lua_pushlstring(state, ret.c_str(), ret.size());
    }

    // read函数
    template<class T>
    inline T read(lua_State *state, int index)
    {
        return (T)lua_touserdata(state, index);
    }

    // 声明
    template<> inline void read(lua_State *state, int index);
    template<> inline bool read(lua_State *state, int index);
    template<> inline char read(lua_State *state, int index);
    template<> inline unsigned char read(lua_State *state, int index);
    template<> inline short read(lua_State *state, int index);
    template<> inline unsigned short read(lua_State *state, int index);
    template<> inline int read(lua_State *state, int index);
    template<> inline unsigned int read(lua_State *state, int index);
    template<> inline long read(lua_State *state, int index);
    template<> inline unsigned long read(lua_State *state, int index);
    template<> inline long long read(lua_State *state, int index);
    template<> inline unsigned long long read(lua_State *state, int index);
    template<> inline float read(lua_State *state, int index);
    template<> inline double read(lua_State *state, int index);   
    template<> inline char* read(lua_State *state, int index);
    template<> inline const char* read(lua_State *state, int index);
    template<> inline const std::string read(lua_State *state, int index);

    // 定义
    template<>
    inline void read(lua_State *state, int index)
    {
        return;
    }

    template<>
    inline bool read(lua_State *state, int index)
    {
        if (lua_isboolean(state, index))
        {
            return lua_toboolean(state, index) != 0;
        }
        else
        {
            return lua_tonumber(state, index) != 0;
        }
    }

    template<>
    inline char read(lua_State *state, int index)
    {
        return (char)lua_tonumber(state, index);
    }

    template<>
    inline unsigned char read(lua_State *state, int index)
    {
        return (unsigned char)lua_tonumber(state, index);
    }

    template<>
    inline short read(lua_State *state, int index)
    {
        return (short)lua_tonumber(state, index);
    }

    template<>
    inline unsigned short read(lua_State *state, int index)
    {
        return (unsigned short)lua_tonumber(state, index);
    }

    template<>
    inline int read(lua_State *state, int index)
    {
        return (int)lua_tonumber(state, index);
    }

    template<>
    inline unsigned int read(lua_State *state, int index)
    {
        return (unsigned int)lua_tonumber(state, index);
    }

#if defined(__X86_64__) || defined(__X86_64) || defined(__amd_64) || defined(__amd_64__)
    template<>
    inline long read(lua_State *state, int index)
    {
        if (lua_isnumber(state, index))
        {
            return (long)lua_tonumber(state, index);
        }
        else
        {
            return *(long*)lua_touserdata(state, index);
        }
    }

    template<>
    inline unsigned long read(lua_State *state, int index)
    {
        if (lua_isnumber(state, index))
        {
            return (unsigned long)lua_tonumber(state, index);
        }
        else
        {
            return *(unsigned long*)lua_touserdata(state, index);
        }
    }
#else
    template<>
    inline long read(lua_State *state, int index)
    {
        return (long)lua_tonumber(state, index);
    }

    template<>
    inline unsigned long read(lua_State *state, int index)
    {
        return (unsigned long)lua_tonumber(state, index);
    }
#endif

    template<>
    inline long long read(lua_State *state, int index)
    {
        if (lua_isnumber(state, index))
        {
            return (long long)lua_tonumber(state, index);
        }
        else
        {
            return *(long long*)lua_touserdata(state, index);
        }
    }

    template<>
    inline unsigned long long read(lua_State *state, int index)
    {
        if (lua_isnumber(state, index))
        {
            return (unsigned long long)lua_tonumber(state, index);
        }
        else
        {
            return *(unsigned long long*)lua_touserdata(state, index);
        }
    }

    template<>
    inline float read(lua_State *state, int index)
    {
        return (float)lua_tonumber(state, index);
    }

    template<>
    inline double read(lua_State *state, int index)
    {
        return (double)lua_tonumber(state, index);
    }

    template<>
    inline char* read(lua_State *state, int index)
    {
        return (char*)lua_tostring(state, index);
    }

    template<>
    inline const char* read(lua_State *state, int index)
    {
        return (const char*)lua_tostring(state, index);
    }

    template<>
    inline const std::string read(lua_State *state, int index)
    {
        size_t size = 0;
        const char *cstr = lua_tolstring(state, index, &size);
        std::string str;
        if (cstr)
        {
            str = cstr;
        }
        return str;
    }

    // pop函数
    template<class T>
    inline T pop(lua_State *state)
    {
        T t = read<T>(state, -1);
        lua_pop(state, 1);
        return t;
    }

    // call_lua共11个版本，支持无参数到拥有10个参数
    template<class T>
    T call_lua(lua_State *state, const char* name)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            if (lua_pcall(state, 0, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1>
    T call_lua(lua_State *state, const char* name, T1 t1)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            if (lua_pcall(state, 1, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            if (lua_pcall(state, 2, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            if (lua_pcall(state, 3, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            if (lua_pcall(state, 4, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            if (lua_pcall(state, 5, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            push(state, t6);
            if (lua_pcall(state, 6, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            push(state, t6);
            push(state, t7);
            if (lua_pcall(state, 7, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            push(state, t6);
            push(state, t7);
            push(state, t8);
            if (lua_pcall(state, 8, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            push(state, t6);
            push(state, t7);
            push(state, t8);
            push(state, t9);
            if (lua_pcall(state, 9, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }

    template<class T, class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
    T call_lua(lua_State *state, const char* name, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
    {
        lua_settop(state, 0);
        lua_pushcfunction(state, lua_error_handler);

        lua_getglobal(state, name);
        if (lua_isfunction(state, -1))
        {
            push(state, t1);
            push(state, t2);
            push(state, t3);
            push(state, t4);
            push(state, t5);
            push(state, t6);
            push(state, t7);
            push(state, t8);
            push(state, t9);
            push(state, t10);
            if (lua_pcall(state, 10, 1, 1) != 0)
            {
                std::cout << "ToluaEngine::call_lua error for pcall " << name << " error." << std::endl;
            }
        }
        else
        {
            std::cout << "ToluaEngine::call_lua error for " << name << " is not function." << std::endl;
        }
        lua_remove(state, -2);
        return pop<T>(state);
    }
}

#endif