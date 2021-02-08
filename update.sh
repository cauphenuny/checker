#!/bin/sh
killall checker
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source
git init
git remote add origin https://github.com/ycpedef/checker
git pull origin master 1> /dev/null 2> /dev/null
pwd
#bash ./copy.sh

