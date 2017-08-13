#ifndef LUA_TINKER_ENGINE_H
#define LUA_TINKER_ENGINE_H

#include "Singleton.h"
#include "LuaTinkerPackage.h"

#include <string>
#include <map>
#include <iostream>
#include <cstdint>

enum EventId
{
    EventZero = 0,
    EventOne,
};

/********************************************************/
/* C++类，单例，负责lua与外部交互                       */
/********************************************************/
class LuaTinkerEngine : public Singleton<LuaTinkerEngine>
{
public:
    LuaTinkerEngine();
    virtual ~LuaTinkerEngine();

public:
    bool ReloadLua();
    bool Init();

    // 注册C++函数用来给lua调用
    bool RegCplusFuncForLua();

    // lua事件，在lua中可多次触发(比如玩家登陆就可能触发多个lua事件)
    void CallLuaEventDispatcher(const std::map<std::string, LuaValue> &para_map, EventId event_id);

    // 获取lua中的value
    std::string GetLuaStringValue(const std::string &name);
    int32_t GetLuaInt32Value(const std::string &name);
    int64_t GetLuaInt64Value(const std::string &name);
    double GetLuaDoubleValue(const std::string &name);

    // 获取lua中table的key
    std::string GetLuaStringTableValue(const std::string &name, const std::string &key);
    int32_t GetLuaInt32TableValue(const std::string &name, const std::string &key);
    int64_t GetLuaInt64TableValue(const std::string &name, const std::string &key);
    double GetLuaDoubleTableValue(const std::string &name, const std::string &key);

public:
    // 测试C++函数，可以调用lua的函数(在lua函数中也可以调用注册的C++函数)
    void TestFun();

    // 测试C++函数，可以取lua中的value
    void TestChannelCenter();

protected:
    LuaTinkerPackage        *package;
    std::string             load_file_name;
};

#define sLuaTinkerEngine (*LuaTinkerEngine::Instance())

#endif