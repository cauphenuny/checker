#!/bin/sh
if [ -f  /bin/checker ]; then
    echo "Warning: rewrite /bin/checker"
fi
rm -rf  ~/.ycpedef_checker_source/
git clone https://github.com/ycpedef/checker.git ~/.ycpedef_checker_source/
cd ~/.ycpedef_checker_source
sh ./compile.sh
