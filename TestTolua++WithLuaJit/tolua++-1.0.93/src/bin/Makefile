all: tolua++

tolua++: tolua.o toluabind.o 
	gcc -g tolua.o toluabind.o -o tolua++ -llua -ltolua++ -L ../lib -L ../../../../TestLua/lua-5.1.4/src -lm 
tolua.o: tolua.c
	gcc -g -c tolua.c  -o tolua.o -I ../../../../TestLua/lua-5.1.4/src  -I ../../include
toluabind.o: toluabind.c
	gcc -g -c toluabind.c  -o toluabind.o -I ../../../../TestLua/lua-5.1.4/src  -I ../../include

clean:
	rm -rf *.o 
	rm -rf tolua++
