#!/bin/sh
echo "compiling..."
g++ -c *.cpp
echo "linking..."
g++ -o checker *.o
echo "delete file..."
rm *.o
