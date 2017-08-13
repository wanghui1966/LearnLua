
g_TestFunc = 
{
    class_name_ = "g_TestFunc",
    file_name_ = "test_func.lua",
}

function func(player, str, data)
    if not player or not str or not data then
        return false
    end
    print(string.format("func:str=%s, data=%d", str, data))

    -- 全局函数示例
    print(string.format("lua::func global_func_example:ret=%s", tostring(global_func_example(data))))

    -- 类函数示例
    print(string.format("lua::func class:player_id=%d, nick_name=%s", player:GetPlayerId(), player:GetNickName()))
    player:SetNickName("xxnigeerhuo")
    print(string.format("lua::func class:player_id=%d, nick_name=%s", player:GetPlayerId(), player:GetNickName()))

    return true
end