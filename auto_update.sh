#!/bin/sh
killall checker
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_update
if [ -f ./master.zip ]; then
    rm -rf ./master.zip
fi
if [ -f ./checker/ ]; then
    rm -rf ./checker/
fi
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zip 2>/dev/null 1>&2
unzip master.zip 2>/dev/null 1>&2
cp -r checker/ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

