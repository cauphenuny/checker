#!/bin/bash
echo -e "\e[1;32m [delete file] \e[0m"
rm -rf ~/.ycpedef_checker_buffer/
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_buffer

echo -e "\e[1;32m [download file] \e[0m"
cd ~/.ycpedef_checker_buffer
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zip
unzip master.zip
cd checker/
cp -r ./ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source

echo -e "\e[1;32m [move file] \e[0m"
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi
rm -rf ~/.ycpedef_checker_source 1>/dev/null 2>&1
