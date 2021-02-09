#!/bin/sh
printf "\e[0;32 delete file ... \e[0"
rm -rf ~/.ycpedef_checker_buffer/
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_buffer

printf "\e[0;32 download file ... \e[0"
cd ~/.ycpedef_checker_buffer
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zip
unzip master.zip
cd checker/
cp -r ./ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source

printf "\e[0;32 move file ... \e[0"
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

rm -rf ~/.ycpedef_checker_source 1>/dev/null 2>&1
