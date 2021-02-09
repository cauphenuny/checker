#!/bin/sh
# echo "delete file ..."
killall checker 1>/dev/null 2>&1
rm -rf ~/.ycpedef_checker_buffer/ 1>/dev/null 2>&1
rm -rf ~/.ycpedef_checker_source 1>/dev/null 2>&1
mkdir -p ~/.ycpedef_checker_source 1>/dev/null 2>&1
mkdir -p ~/.ycpedef_checker_buffer 1>/dev/null 2>&1

# echo "download file ..."
cd ~/.ycpedef_checker_buffer 1>/dev/null 2>&1
wget https://github.com/ycpedef/checker/repository/archive/master.zip 1>/dev/null 2>&1
unzip master.zip 1>/dev/null 2>&1
cd checker/
cp -r ./ ~/.ycpedef_checker_source 1>/dev/null 2>&1
cd ~/.ycpedef_checker_source 1>/dev/null 2>&1

# echo "move file ..."
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

rm -rf ~/.ycpedef_checker_buffer 1>/dev/null 2>&1

