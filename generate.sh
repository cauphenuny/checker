#!/bin/bash
#list="checker.cpp checker color.h compile.sh install.sh"
#echo $list
echo "compile checker.cpp ..."
g++ checker.cpp -o checker -lreadline
./upload.sh
