#!/bin/sh
# echo "delete file ..."
killall checker
if [ -f ~/.ycpedef_checker_buffer ]; then
    rm -rf ~/.ycpedef_checker_buffer/
fi
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_buffer

# echo "download file ..."
cd ~/.ycpedef_checker_buffer 1>/dev/null 2>&1
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zip 1>/dev/null 2>&1
unzip master.zip 1>/dev/null 2>&1
cp -r checker/ ~/.ycpedef_checker_source 1>/dev/null 2>&1
cd ~/.ycpedef_checker_source 1>/dev/null 2>&1

# echo "move file ..."
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi
