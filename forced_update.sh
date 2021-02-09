#!/bin/bash
echo -e "\e[1;32m[delete file] \e[0m"
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source

echo -e "\e[1;32m[download file] \e[0m"
cd ~/.ycpedef_checker_source
git clone https://github.com/ycpedef/checker ./ --depth=1

echo -e "\e[1;32m[move file] \e[0m"
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi
