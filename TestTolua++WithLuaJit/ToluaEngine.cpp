#include "ToluaEngine.h"

#include "pkg_export/player_export.h"
#include "pkg_export/global_func_export.h"

#include "pkg_source/player.h"

#include "ToluaPackage.h"

ToluaEngine::ToluaEngine() : state(nullptr)
{
    
}

ToluaEngine::~ToluaEngine()
{
    if (state)
    {
        lua_close(state);
    }
    state = nullptr;
}

bool ToluaEngine::ReloadLua()
{
    return ToluaPackage::call_lua<bool>(state, "ReloadAllScript");
}

bool ToluaEngine::Init()
{
    state = luaL_newstate();
    if (state == nullptr)
    {
        return false;
    }
    load_file_name = "lua/entry.lua";

    luaL_openlibs(state);
    tolua_open(state);

    InitLuaExport();
    
    lua_pushcfunction(state, ToluaPackage::lua_error_handler);
    if (luaL_loadfile(state, load_file_name.c_str()) != 0) 
    {
        return false;
    }

    if (lua_pcall(state, 0, LUA_MULTRET, 1) != 0) 
    {
        return false;
    }

    return true;
}

void ToluaEngine::InitLuaExport()
{
    tolua_global_func_open(state);

    tolua_player_open(state);
}

void ToluaEngine::TestFun()
{
    std::string str = "ToluaEngine::TestFun";
    int32_t data = 10;

    Player *player = new Player(1, "xx11xx");
    bool ret = ToluaPackage::call_lua<bool>(state, "func", player, str, data);

    std::cout << "ToluaEngine::TestFunc:ret=" << ret << std::endl;
}
