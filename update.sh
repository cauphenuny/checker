#!/bin/bash
echo -e "\e[1;32m[delete file] \e[0m"
rm -rf /tmp/checker/buffer/
rm -rf /tmp/checker/source
mkdir -p /tmp/checker/source
mkdir -p /tmp/checker/buffer

echo -e "\e[1;32m[download file] \e[0m"
cd /tmp/checker/buffer
wget https://gitee.com/yuanchenpu/checker/repository/archive/$1.zip
unzip $1.zip
cd checker/
cp -r ./ /tmp/checker/source

echo -e "\e[1;32m[compile] \e[0m"
cd /tmp/checker/source
make

echo -e "\e[1;32m[move file] \e[0m"
if [ -f /tmp/checker/source/copy.sh ]; then
    /tmp/checker/source/copy.sh
fi
rm -rf /tmp/checker/source 1>/dev/null 2>&1
