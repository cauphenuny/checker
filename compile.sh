#!/bin/bash
echo "compiling..."
g++ -c *.cpp
if [ $? != 0 ]; then
    echo -e "\nFailed."
    exit 1
fi
echo "linking..."
g++ -o checker *.o
if [ $? != 0 ]; then
    echo -e "\nFailed."
    exit 1
fi
echo "delete file..."
rm *.o
if [ $? != 0 ]; then
    echo -e "\nFailed."
    exit 1
fi
echo -e "\e[1;32msucceeded!\e[0m"

