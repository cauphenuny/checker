#!/bin/sh
if [ -f  /bin/checker ]; then
    echo "Warning: rewrite /bin/checker"
fi
rm -rf  ~/.ycpedef_checker_source/
cp -r ./ ~/.ycpedef_checker_source
cd ~/.ycpedef_checker_source
git pull origin master

wget -c ftp://ftp.gnu.org/gnu/readline/readline-6.2.tar.gz 
tar -zxvf readline-6.2.tar.gz 
cd readline-6.2
./configure
make && make installl
ldconfig

sh ./compile.sh
