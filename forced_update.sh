#!/bin/sh
echo "delete file ..."
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
echo "download file ..."
git clone https://gitee.com/ycpedef/checker ~/.ycpedef_checker_source 1> /dev/null 2>&1
cd ~/.ycpedef_checker_source
echo "move file ..."
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi
