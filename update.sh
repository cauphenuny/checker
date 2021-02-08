#!/bin/sh
killall checker
cd ~/.ycpedef_checker_source
git pull origin master 1> /dev/null 2> /dev/null
sh copy.sh
