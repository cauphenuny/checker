#!/bin/sh
echo "git add ."
git add .
date +"%F %T" | xargs -d'\n' -t git commit -m
echo "git push -u gitee compatible"
git push -u gitee compatible
echo "git push -u origin compatible"
git push -u origin compatible
