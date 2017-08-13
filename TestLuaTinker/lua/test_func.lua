
g_TestFunc = 
{
    class_name_ = "g_TestFunc",
    file_name_ = "test_func.lua",
}

function func(str, data)
    if not str or not data then
        return false
    end
    -- 全局函数示例
    print("lua::test GlobalFuncExample1:"..GlobalFuncExample1(data))
    print("lua::test GlobalFuncExample2:"..GlobalFuncExample2())

    -- 类函数示例
    gClassExample:SetData(12)
    print("lua::test class:data="..gClassExample:GetData())

    return true
end