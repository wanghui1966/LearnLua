
g_LuaOne = 
{
    class_name_ = "g_LuaOne",
    file_name_ = "lua_one.lua",
}

function g_LuaOne:Entry(args)
    local id = args["id"]
    local name = args["name"]

    if not id or not name then
        return
    end

    print("g_LuaOne:id="..id..",name="..name)
end