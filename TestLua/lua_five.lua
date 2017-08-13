require "student_lib"

-- 第一个学生
local student_1 = student_lib.NewStudent()
local id = student_lib.GetId(student_1)
local name = student_lib.GetName(student_1)
print(string.format("student_1:id=%d, name=%s", id, name))

student_lib.SetName(student_1, "huiwang");
id = student_lib.GetId(student_1)
name = student_lib.GetName(student_1)
print(string.format("student_1:id=%d, name=%s", id, name))

--第二个学生
local student_2 = student_lib.NewStudent()
id = student_lib.GetId(student_2)
name = student_lib.GetName(student_2)
print(string.format("student_2:id=%d, name=%s", id, name))
