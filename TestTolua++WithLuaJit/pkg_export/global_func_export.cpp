/*
** Lua binding: global_func
** Generated automatically by tolua++-1.0.92 on Sun Aug 13 15:57:48 2017.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_global_func_open (lua_State* tolua_S);

#include "../pkg_source/global_func.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: global_func_example */
#ifndef TOLUA_DISABLE_tolua_global_func_global_func_example00
static int tolua_global_func_global_func_example00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int data = ((int)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  global_func_example(data);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'global_func_example'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_global_func_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,"global_func_example",tolua_global_func_global_func_example00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_global_func (lua_State* tolua_S) {
 return tolua_global_func_open(tolua_S);
};
#endif

