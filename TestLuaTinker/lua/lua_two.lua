
g_LuaTwo = 
{
    class_name_ = "g_LuaTwo",
    file_name_ = "lua_two.lua",
}

function g_LuaTwo:Entry(args)
    local id = args["id"]
    local name = args["name"]

    if not id or not name then
        return
    end

    print("g_LuaTwo:id="..id..",name="..name)
end