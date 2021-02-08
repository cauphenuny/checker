#!/bin/sh
echo "delete file ..."
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source

echo "download file ..."
git clone https://github.com/ycpedef/checker ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source

echo "move file ..."
killall checker
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi
