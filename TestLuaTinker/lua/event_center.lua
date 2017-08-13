
g_EventCenter = 
{
    class_name_ = "g_EventCenter",
    file_name_ = "event_center.lua",
    entry_list = {}
}

g_EventCenter.event = 
{
    [1] = "event_one",
}

function g_EventCenter:New()
    local instance = {}
    setmetatable(instance, self)
    self.__index = self
    return instance
end

function g_EventCenter:Trigger(event_name, args)
    if not event_name or not args or not self.entry_list[event_name] then
        return
    end

    for k, v in pairs(self.entry_list[event_name]) do
        if type(v["Entry"]) == "function" then
            v:Entry(args)
        end
    end
end

function g_EventCenter:Setup(event_name, event_class)
    if not event_name or not event_class then
        return
    end
    if not self.entry_list[event_name] then
        self.entry_list[event_name] = {}
    end
    table.insert(self.entry_list[event_name], event_class)
end

function g_EventCenter:Dispatch(event_id)
    local func = self.event[event_id]
    if not func then
        return
    end

    g_EventCenter:Trigger(func, __args)
end

_G.EventDispatcher = function(event_id)
    g_EventCenter:Dispatch(event_id)
end

g_EventCenter:Setup("event_one", g_LuaOne)
g_EventCenter:Setup("event_one", g_LuaTwo)