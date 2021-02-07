#!/bin/bash
list="readline/ checker.cpp checker color.h compile.sh install.sh"
echo $list
zip -q -r checker$1.zip $list
echo "------"
ls --color=auto
