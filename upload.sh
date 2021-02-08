#!/bin/sh
#./compile.sh
echo "git add ."
git add .
date +"%F_%T" | xargs -t git commit -m
echo "git push -u gitee master"
git push -u gitee master
echo "git push -u origin master"
git push -u origin master
