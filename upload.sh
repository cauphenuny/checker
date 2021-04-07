#!/bin/sh
echo "git add ."
git add .
git commit -m "$2"
echo "git push -u gitee "$1
git push -u gitee $1
echo "git push -u origin "$1
git push -u origin $1
