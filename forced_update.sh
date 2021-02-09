#!/bin/bash
printf "----- [delete file] -----"
rm -rf ~/.ycpedef_checker_buffer/
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_buffer

printf "----- [download file] -----"
cd ~/.ycpedef_checker_buffer
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zip
unzip master.zip
cd checker/
cp -r ./ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source

printf "----- [move file] -----"
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

rm -rf ~/.ycpedef_checker_source 1>/dev/null 2>&1
