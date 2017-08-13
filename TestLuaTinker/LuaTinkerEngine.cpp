#include "LuaTinkerEngine.h"
#include "ClassExample.h"

// 需要注册的全局函数
static int32_t GlobalFuncExample1(int32_t data)
{
    return (data * 2);
}
// 如果想要特定返回值，则使用此函数，需遵循函数指针规则
static int GlobalFuncExample2(lua_State *state)
{
    std::string str = "GlobalFuncExample2 str";
    lua_pushlstring(state, str.c_str(), str.length());
    return 1;
}

LuaTinkerEngine::LuaTinkerEngine() : package(nullptr)
{

}

LuaTinkerEngine::~LuaTinkerEngine()
{
    if (package)
    {
        delete package;
    }
    package = nullptr;
}

bool LuaTinkerEngine::ReloadLua()
{
    return package->call_lua<bool>("ReloadAllScript");
}

bool LuaTinkerEngine::Init()
{
    package = new LuaTinkerPackage;
    if (package == nullptr)
    {
        return false;
    }
    load_file_name = "lua/entry.lua";

    if (!package->init(load_file_name.c_str()))
    {
        return false;
    }

    return RegCplusFuncForLua();
}

bool LuaTinkerEngine::RegCplusFuncForLua()
{
    if (package == nullptr)
    {
        return false;
    }

    // 注册全局函数示例
    package->reg_func<int32_t(int32_t)>("GlobalFuncExample1", GlobalFuncExample1);
    package->reg_func<lua_CFunction>("GlobalFuncExample2", GlobalFuncExample2);

    // 注册单例类
    package->reg_class<ClassExample>("ClassExample");
    package->reg_class_con_func<ClassExample>();
    package->reg_class_func<ClassExample>("SetData", &ClassExample::SetData);
    package->reg_class_func<ClassExample>("GetData", &ClassExample::GetData);
    package->setglobal("gClassExample", ClassExample::Instance());
}

void LuaTinkerEngine::CallLuaEventDispatcher(const std::map<std::string, LuaValue> &para_map, EventId event_id)
{
    lua_tinker::table ltable(package->get_lua_state(), "__args");

    for (std::map<std::string, LuaValue>::const_iterator it = para_map.begin(); it != para_map.end(); ++it)
    {
        switch (it->second.type)
        {
        case NULL_TYPE:
            break;
        case INT32_TYPE:
            ltable.set(it->first.c_str(), it->second.value.int32_value);
            break;
        case UINT32_TYPE:
            ltable.set(it->first.c_str(), it->second.value.uint32_value);
            break;
        case INT64_TYPE:
            ltable.set(it->first.c_str(), it->second.value.int64_value);
            break;
        case UINT64_TYPE:
            ltable.set(it->first.c_str(), it->second.value.uint64_value);
            break;
        case DOUBLE_TYPE:
            ltable.set(it->first.c_str(), it->second.value.double_value);
            break;
        case STRING_TYPE:
            ltable.set(it->first.c_str(), it->second.value.string_value);
            break;
        case PTR_TYPE:
            ltable.set(it->first.c_str(), it->second.value.ptr_value);
            break;
        default:
            break;
        }
    }

    package->call_lua<void>("EventDispatcher", event_id);
}

std::string LuaTinkerEngine::GetLuaStringValue(const std::string &name)
{
    lua_tinker::lua_lstring lua_str(const_cast<char*>(name.c_str()), name.length());
    return package->call_lua<const char*>("__get_value", &lua_str);
}

int32_t LuaTinkerEngine::GetLuaInt32Value(const std::string &name)
{
    std::string ret = GetLuaStringValue(name);
    return atoi(ret.c_str());
}

int64_t LuaTinkerEngine::GetLuaInt64Value(const std::string &name)
{
    std::string ret = GetLuaStringValue(name);
    return atoll(ret.c_str());
}

double LuaTinkerEngine::GetLuaDoubleValue(const std::string &name)
{
    std::string ret = GetLuaStringValue(name);
    return atof(ret.c_str());
}

std::string LuaTinkerEngine::GetLuaStringTableValue(const std::string &name, const std::string &key)
{
    lua_tinker::lua_lstring lua_str_name(const_cast<char*>(name.c_str()), name.length());
    lua_tinker::lua_lstring lua_str_key(const_cast<char*>(key.c_str()), key.length());
    return package->call_lua<const char*>("__get_table_value", &lua_str_name, &lua_str_key);
}

int32_t LuaTinkerEngine::GetLuaInt32TableValue(const std::string &name, const std::string &key)
{
    std::string ret = GetLuaStringTableValue(name, key);
    return atoi(ret.c_str());
}

int64_t LuaTinkerEngine::GetLuaInt64TableValue(const std::string &name, const std::string &key)
{
    std::string ret = GetLuaStringTableValue(name, key);
    return atoll(ret.c_str());
}

double LuaTinkerEngine::GetLuaDoubleTableValue(const std::string &name, const std::string &key)
{
    std::string ret = GetLuaStringTableValue(name, key);
    return atof(ret.c_str());
}

void LuaTinkerEngine::TestFun()
{
    std::cout << "====LuaTinkerEngine::TestFun begin====" << std::endl;

    std::string str = "TestFun";
    int32_t data = 10;

    lua_tinker::lua_lstring lua_str(const_cast<char*>(str.c_str()), str.length());
    bool ret = package->call_lua<bool>("func", &lua_str, data);

    std::cout << "LuaTinkerEngine::TestFunc:ret=" << ret << std::endl;

    std::map<std::string, LuaValue> para_map;
    int32_t id = 1;
    para_map["id"] = LuaValue(id);
    std::string name = "xx";
    para_map["name"] = LuaValue(name);
    CallLuaEventDispatcher(para_map, EventId::EventOne);

    std::cout << "====LuaTinkerEngine::TestFun end====" << std::endl;
}

void LuaTinkerEngine::TestChannelCenter()
{
    std::cout << "====LuaTinkerEngine::TestChannelCenter begin====" << std::endl;

    std::cout << "int32_value=" << GetLuaInt32Value("channel.value.int32value") << std::endl;
    std::cout << "int64_value=" << GetLuaInt64Value("channel.value.int64value") << std::endl;
    std::cout << "double_value=" << GetLuaDoubleValue("channel.value.doublevalue") << std::endl;
    std::cout << "str_value=" << GetLuaStringValue("channel.value.stringvalue") << std::endl;

    std::cout << "table:id=" << GetLuaInt32TableValue("channel.table_value.example1", "id") << std::endl;
    std::cout << "table:name=" << GetLuaStringTableValue("channel.table_value.example1", "name") << std::endl;
    std::cout << "table:score=" << GetLuaDoubleTableValue("channel.table_value.example1", "score") << std::endl;

    std::cout << "====LuaTinkerEngine::TestChannelCenter end====" << std::endl;
}