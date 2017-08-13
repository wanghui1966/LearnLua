
g_TestValue = 
{
    class_name_ = "g_TestValue",
    file_name_ = "test_value.lua",
}

-- 全局value
g_ChannelCenter:SetValue("channel.value.stringvalue", "I an a string.")
g_ChannelCenter:SetValue("channel.value.int32value", 2011112222)
g_ChannelCenter:SetValue("channel.value.int64value", -20111122224444)
g_ChannelCenter:SetValue("channel.value.doublevalue", 2011112222.4444)

-- table value
local tb = {
    ["id"] = 1,
    ["name"] = "huiwang",
    ["score"] = 88.9
}
g_ChannelCenter:SetTable("channel.table_value.example1", tb)
tb.id = 2