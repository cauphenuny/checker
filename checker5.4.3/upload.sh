#!/bin/sh
echo "git add ."
git add .
date +"%F %T" | xargs -d'\n' -t git commit -m
echo "git push -u gitee master"
git push -u gitee master
echo "git push -u origin master"
git push -u origin master
