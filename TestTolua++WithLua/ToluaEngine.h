#ifndef TOLUA_ENGINE_H
#define TOLUA_ENGINE_H

#include "Singleton.h"

#include <iostream>
#include <string>
#include <cstring>

#include "tolua++.h"
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
};

class ToluaEngine : public Singleton<ToluaEngine>
{
public:
    ToluaEngine();
    virtual ~ToluaEngine();

public:
    bool ReloadLua();
    bool Init();

protected:
    void InitLuaExport();

public:
    void TestFun();

protected:
    lua_State               *state;
    std::string             load_file_name;
};

#define sToluaEngine (*ToluaEngine::Instance())

#endif
