#!/bin/bash
echo "compiling..."
ls *.cpp | xargs -I % bash -c 'echo compiling % ... && g++ -c %'
echo "linking..."
g++ -o checker *.o
if [ $? != 0 ]; then
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

