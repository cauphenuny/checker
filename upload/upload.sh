#!/bin/sh
echo "git add ."
git add .
date +"%F %T" | xargs -d'\n' -t git commit -m
echo "git push -u gitee dev"
git push -u gitee dev
echo "git push -u origin dev"
git push -u origin dev
