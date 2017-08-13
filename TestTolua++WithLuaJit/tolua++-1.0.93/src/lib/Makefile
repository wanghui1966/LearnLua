all: libtolua++.a

libtolua++.a: tolua_event.o tolua_is.o tolua_map.o tolua_push.o tolua_to.o
	ar -v -q  libtolua++.a tolua_event.o tolua_is.o tolua_map.o tolua_push.o tolua_to.o

tolua_event.o: tolua_event.c
	gcc -g -c tolua_event.c  -o tolua_event.o -I ../../../../TestLuaJit/LuaJIT-2.0.4/src  -I ../../include
tolua_is.o: tolua_is.c
	gcc -g -c tolua_is.c  -o tolua_is.o -I ../../../../TestLuaJit/LuaJIT-2.0.4/src  -I ../../include
tolua_map.o: tolua_map.c
	gcc -g -c tolua_map.c  -o tolua_map.o -I ../../../../TestLuaJit/LuaJIT-2.0.4/src  -I ../../include
tolua_push.o: tolua_push.c
	gcc -g -c tolua_push.c -o tolua_push.o -I ../../../../TestLuaJit/LuaJIT-2.0.4/src  -I ../../include
tolua_to.o: tolua_to.c
	gcc -g -c tolua_to.c -o tolua_to.o -I ../../../../TestLuaJit/LuaJIT-2.0.4/src  -I ../../include

clean:
	rm -rf *.o 
	rm -rf libtolua++.a
