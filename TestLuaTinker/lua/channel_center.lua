
g_ChannelCenter = 
{
    class_name_ = "g_ChannelCenter",
    file_name_ = "channel_center.lua",
    channel_list = {}
}

function g_ChannelCenter:New()
    local instance = {}
    setmetatable(instance, self)
    self.__index = self
    return instance
end

-- 存储一个table
function g_ChannelCenter:SetTable(name, tb)
    if not name or not tb then
        return
    end

    if (type(name) == "string") and (type(tb) == "table") then
        self.channel_list[name] = tb
    end
end

-- 读取一个table中的key
function g_ChannelCenter:GetTableValue(name, key)
    if not name or not key then
        return ""
    end

    if not self.channel_list[name] or not self.channel_list[name][key] then
        return ""
    end

    return self.channel_list[name][key]
end

-- 存储一个value(支持string和number类型)
function g_ChannelCenter:SetValue(name, value)
    if not name or not value then
        return
    end

    if (type(name) == "string") and ((type(value) == "string") or (type(value) == "number")) then
        self.channel_list[name] = value
    end
end

-- 读取一个value，一律返回一个string，到C++层后自己转
function g_ChannelCenter:GetValue(name)
    if not name then
        return ""
    end

    if not self.channel_list[name] then
        return ""
    end

    return self.channel_list[name]
end

_G.__get_table_value = function(name, key) return g_ChannelCenter:GetTableValue(name, key) end
_G.__get_value = function(name) return g_ChannelCenter:GetValue(name) end