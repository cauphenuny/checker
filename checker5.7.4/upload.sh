#!/bin/sh
echo "git add ."
git add .
date +"%F %T" | xargs -d'\n' -t git commit -m
echo "git push -u gitee "$1
git push -u gitee $1
echo "git push -u origin "$1
git push -u origin $1
