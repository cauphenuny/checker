#!/bin/bash
echo "compiling ..."
ls *.cpp | xargs -I % bash -c 'echo compiling % ... && g++ -c %; if [ $? != 0 ]; then exit 1; fi'
echo "linking ..."
g++ -o checker -lreadline *.o
if [ ! $? ]; then
    echo -e "\nFailed."
    exit 1
fi
echo "delete *.o files ..."
rm *.o
if [ $? != 0 ]; then
    echo -e "\nFailed."
    exit 1
fi
echo -e "\e[1;32msucceeded!\e[0m"

