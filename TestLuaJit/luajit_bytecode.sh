
#使用luajit将lua代码编译成二进制文件需要安装luajit
#1. cd thirdlib\LuaJIT-2.0.4
#2. make install

echo -e "\033[41;36m luajit create bytecode begin \033[0m"

current_dir=$(cd "$(dirname "$0")"; pwd)

luajit_exec=luajit

lua_resource_dir=$current_dir/lua_resource
lua_bytecode_dir=$current_dir/lua

rm -rf $lua_bytecode_dir
mkdir -p $lua_bytecode_dir

# 参数分别为：存放lua源文件目录 存放lua二进制文件目录
function luajit_bytecode()
{
    for ele in `ls $1`
    do
        whole_resource_ele=$1"/"$ele
        whole_bytecode_ele=$2"/"$ele
        # 如果为目录
        if [ -d $whole_resource_ele ]; then
            mkdir -p $whole_bytecode_ele
            luajit_bytecode $whole_resource_ele $whole_bytecode_ele
        # 如果为文件，lua文件则生成二进制文件，非lua文件则cp
        elif [ -f $whole_resource_ele ]; then
            file_type=${whole_resource_ele##*.}
            if test $file_type = "lua" ; then
                $luajit_exec -b $whole_resource_ele $whole_bytecode_ele
            else
                echo "cp $whole_resource_ele"
                cp $whole_resource_ele $whole_bytecode_ele
            fi
        fi
    done
}

luajit_bytecode $lua_resource_dir $lua_bytecode_dir

echo -e "\033[41;36m luajit create bytecode end \033[0m"
