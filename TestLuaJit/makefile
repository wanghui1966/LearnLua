
LIB_OPTION=-ILuaJIT-2.0.4/src -LLuaJIT-2.0.4/src -lluajit -std=c++11

all:lua_one lua_two lua_three lua_four
.PHONY:all

lua_one:lua_one.cpp
	g++ lua_one.cpp -o lua_one $(LIB_OPTION)

lua_two:lua_two.cpp
	g++ lua_two.cpp -o lua_two $(LIB_OPTION)

lua_three:lua_three.cpp
	g++ lua_three.cpp -o lua_three $(LIB_OPTION)

lua_four:lua_four.cpp
	g++ lua_four.cpp -o lua_four $(LIB_OPTION)

.PHONY:clean
clean:
	rm -f lua_one
	rm -f lua_two
	rm -f lua_three
	rm -f lua_four
