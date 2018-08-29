#!/bin/bash
duty=$1
file=$2
echo "duty=${duty}"
if [ -z ${duty} ]; then
	echo "please input duty."
	exit
fi
if [ -z ${file} ]; then
	echo "please input file."
	exit
fi
sed -i '4c #define X_MAX_TYPE_NUM '${duty}'' $file
x_table="{"
for((i=0;i<${duty};i++))
{
	x_table=${x_table}"\"YEAR${i}\", "
}
x_table=${x_table}"},"
sed -i "8s/^.*$/${x_table}/"  $file
gcc $file 
./a.out
