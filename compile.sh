#!/bin/bash
ls *.cpp | xargs -t -I % g++ -c %
echo 'g++ -o checker -lreadline *.o'
g++ -o checker *.o -lreadline
if [ $? != 0 ]; then exit 1; fi
ls *.o | xargs -t -I % rm %
if [ $? != 0 ]; then exit 1; fi
if [ -x ./checker ]; then
    echo -e "\e[1;32msucceeded!\e[0m"
else
    exit 1
fi

