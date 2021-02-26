#!/bin/bash
# echo "delete file ..."
killall checker &>/dev/null
rm -rf ~/.ycpedef_checker_buffer/ &>/dev/null
rm -rf ~/.ycpedef_checker_source &>/dev/null
mkdir -p ~/.ycpedef_checker_source &>/dev/null
mkdir -p ~/.ycpedef_checker_buffer &>/dev/null

# echo "download file ..."
cd ~/.ycpedef_checker_buffer &>/dev/null
wget https://gitee.com/yuanchenpu/checker/repository/archive/$1.zip &>/dev/null
unzip $1.zip &>/dev/null
cd checker/ &>/dev/null
cp -r ./ ~/.ycpedef_checker_source &>/dev/null
cd ~/.ycpedef_checker_source &>/dev/null

# echo "move file ..."
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh &>/dev/null
fi

rm -rf ~/.ycpedef_checker_buffer &>/dev/null


