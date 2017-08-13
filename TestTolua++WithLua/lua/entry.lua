
-- 此处是为了避免entry.lua文件多次加载导致的问题
-- 也可以在ReloadAllScript函数里单独处理(entry.lua文件不加载)
if _load_main_script then
    return
end

package.path = package.path.."./?.lua;"

local LOADED = debug.getregistry()._LOADED
_load_main_script = {}
for k, v in pairs(LOADED) do
    _load_main_script[k] = v
end

local function foreach_file(folder, cb)
    local pf = io.popen("ls -l " .. folder)
    local s = pf:read("*a")
    pf:close()
    local siter = s:gmatch("([^\n]+)")
    siter() --忽略第一行
    for l in siter do
        for privalege, name in l:gmatch("([%w%-]+).+ ([^\n]+)") do
            if privalege:find("d") then
                foreach_file(folder .. '/' .. name, cb)
            else
                cb(folder .. '/' .. name)
            end
        end
    end
end

local function loadscript(file)
    if file:sub(-4, -1) ~= ".lua" then
        return
    end
    file = file:sub(1, -5)
    file = file:gsub('/', '.')
    require(file)
end

local function ReleaseAllScript()
    for file, free in pairs(LOADED) do
        if not _load_main_script[file] then
            LOADED[file] = nil
            if type(free) == "function" then
                free()
            end
        end
    end
end

function ReloadAllScript()
    ReleaseAllScript()

    -- 此处需注意先后顺序
    foreach_file("lua", loadscript)

    collectgarbage()
    return true
end

ReloadAllScript()