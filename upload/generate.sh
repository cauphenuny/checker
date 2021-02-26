#!/bin/sh
cd ..
echo "compile ..."
g++ *.cpp -o checker -lreadline
upload/upload.sh
