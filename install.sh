#!/bin/sh
if [ -f  /bin/checker ]; then
    echo "Warning: rewrite /bin/checker"
fi

sudo apt install  libreadline-dev git

rm -rf  ~/.ycpedef_checker_source/
cp -r ./ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source
git pull origin master

sh ./compile.sh
