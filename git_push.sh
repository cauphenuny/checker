#!/bin/sh
./checker -v > version.log
echo "git add ."
git add .
date +"%F_%T" | xargs -t git commit -m
echo "git push -u origin master"
git push -u origin master
