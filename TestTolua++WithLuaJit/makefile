
LIB_OPTION=-I../TestLuaJit/LuaJIT-2.0.4/src -Itolua++-1.0.93/include -L../TestLuaJit/LuaJIT-2.0.4/src -Ltolua++-1.0.93/src/lib -lluajit -ltolua++ -std=c++11 

all:main
.PHONY:all

main:main.cpp ToluaEngine.cpp
	g++ main.cpp ToluaEngine.cpp pkg_export/*.cpp pkg_source/*.cpp -o main $(LIB_OPTION)

.PHONY:clean
clean:
	rm -f main
	rm -f pkg_export/*.h
	rm -f pkg_export/*.cpp
	rm -f pkg_export/*.log
