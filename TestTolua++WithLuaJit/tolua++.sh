export LD_LIBRARY_PATH=/usr/local/luajit/lib:$LD_LIBRARY_PATH

current_dir=$(cd "$(dirname "$0")"; pwd)
pkg_dir=$current_dir/pkg_export

tolua_exec=$current_dir/tolua++-1.0.93/src/bin/tolua++

pkg_file_list=(`find $pkg_dir -iname *.pkg`)

printf "\ntolua process start.\n\n"

#由于pkg文件均处于$pkg_dir目录，因此，只需要在这个目录即可
cd $pkg_dir
rm -f $pkg_dir/*.h
rm -f $pkg_dir/*.cpp
rm -f $pkg_dir/*.log

for pkg in ${pkg_file_list[@]};do
	pkg_file_name=${pkg%.*}

	$tolua_exec -o ${pkg_file_name}_export.cpp $pkg > $pkg_dir/tolua_process.log
	$tolua_exec -H ${pkg_file_name}_export.h $pkg > $pkg_dir/tolua_process.log

	printf "%s process done.\n" $pkg
done

printf "\ntolua process end.\n\n"
