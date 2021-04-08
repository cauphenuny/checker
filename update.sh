#!/bin/bash
echo -e "\e[1;32m[delete file] \e[0m" && \
rm -rf /tmp/checker/buffer/ && \
rm -rf /tmp/checker/source && \
mkdir -p /tmp/checker/source && \
mkdir -p /tmp/checker/buffer && \

echo -e "\e[1;32m[download file] \e[0m" && \
cd /tmp/checker/buffer && \
wget https://gitee.com/yuanchenpu/checker/repository/archive/$1.zip && \
unzip $1.zip && \
cd checker/ && \
cp -r ./ /tmp/checker/source && \

echo -e "\e[1;32m[compile] \e[0m" && \
cd /tmp/checker/source && \
make && \

echo -e "\e[1;32m[move file] \e[0m" && \
/tmp/checker/source/copy.sh && \
rm -rf /tmp/checker/source

ret=$?
if [ $ret != 0 ]; then
    echo -e "\n\e[31mshell return $ret, failed.\e[0m"
else
    if [ ! $(command -v checker) ]; then
        echo -e "\n\e[31mcan not find command \`checker\`, failed.\e[0m"
        exit 1
    else
        echo -e "\n\e[32msuccess!\e[0m"
        checker -v
    fi
fi
exit $ret
 
