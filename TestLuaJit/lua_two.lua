local s = "cool"
str = string.format("I am so %s!", s)
tb = { id = 1, name = "x" }

function get_str(a, b)
	return str.format("%d+%s", a, b)
end
