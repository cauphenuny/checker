#!/bin/sh
echo "delete file ..."
killall checkerg
rm -rf ~/.ycpedef_checker_buffer/g
rm -rf ~/.ycpedef_checker_sourceg
mkdir -p ~/.ycpedef_checker_sourceg
mkdir -p ~/.ycpedef_checker_bufferg

echo "download file ..."
cd ~/.ycpedef_checker_bufferg
wget https://gitee.com/yuanchenpu/checker/repository/archive/master.zipg
unzip master.zipg
cp -r checker/ ~/.ycpedef_checker_sourceg
cd ~/.ycpedef_checker_sourceg

echo "move file ..."
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

