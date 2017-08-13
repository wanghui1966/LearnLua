
LIB_OPTION=-I../TestLua/lua-5.1.4/src -ILuaTinker -L../TestLua/lua-5.1.4/src -llua -std=c++11

all:main
.PHONY:all

main:main.cpp LuaTinkerEngine.cpp LuaTinker/lua_tinker.cpp
	g++ main.cpp LuaTinkerEngine.cpp LuaTinker/lua_tinker.cpp -o main $(LIB_OPTION)

.PHONY:clean
clean:
	rm -f main
