#!/bin/sh
echo "compile checker.cpp ..."
g++ checker.cpp -o checker -lreadline
g++ checker.cpp -o /bin/checker -lreadline
