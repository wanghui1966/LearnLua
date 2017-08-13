
LIB_OPTION=-Ilua-5.1.4/src -Llua-5.1.4/src -llua -std=c++11

all:lua_one lua_two lua_three lua_four lua_five lua_six
.PHONY:all

lua_one:lua_one.cpp
	g++ lua_one.cpp -o lua_one $(LIB_OPTION)

lua_two:lua_two.cpp
	g++ lua_two.cpp -o lua_two $(LIB_OPTION)

lua_three:lua_three.cpp
	g++ lua_three.cpp -o lua_three $(LIB_OPTION)

lua_four:lua_four.cpp
	g++ lua_four.cpp -o lua_four $(LIB_OPTION)

lua_five:lua_five.cpp
	g++ lua_five.cpp -o lua_five $(LIB_OPTION)

lua_six:lua_six.cpp
	g++ lua_six.cpp -o lua_six $(LIB_OPTION)

.PHONY:clean
clean:
	rm -f lua_one
	rm -f lua_two
	rm -f lua_three
	rm -f lua_four
	rm -f lua_five
	rm -f lua_six
