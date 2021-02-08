#!/bin/sh
killall checker
cd ~/.ycpedef_checker_source
git pull origin master
sh copy.sh
