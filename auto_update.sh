#!/bin/sh
killall checker
rm -rf ~/.ycpedef_checker_source
mkdir -p ~/.ycpedef_checker_source
git clone https://github.com/ycpedef/checker ~/.ycpedef_checker_source 2> /dev/null 1>&2
cd ~/.ycpedef_checker_source
if [ -f ~/.ycpedef_checker_source/copy.sh ]; then
    ~/.ycpedef_checker_source/copy.sh
fi

