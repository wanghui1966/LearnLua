require "student_lib"

-- 第一个学生
local student_1 = student_lib.NewStudent()--[[
local id = student_lib:GetId()
local name = student_lib:GetName()
print(string.format("student_1:id=%d, name=%s", id, name))

student_lib:SetName("huiwang");
id = student_lib:GetId()
name = student_lib:GetName()
print(string.format("student_1:id=%d, name=%s", id, name))

-- 第二个学生
local student_2 = student_lib.NewStudent()
id = student_lib:GetId()
name = student_lib:GetName()
print(string.format("student_2:id=%d, name=%s", id, name))
]]--