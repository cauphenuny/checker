#!/bin/bash
ls *.cpp | xargs -t -I % g++ -c %
echo 'g++ -o checker -lreadline *.o'
g++ -o checker -lreadline *.o
if [ ! $? ]; then exit 1; fi
ls *.o | xargs -t -I % rm %
if [ ! $? ]; then exit 1; fi
if [ -x ./checker ]; then
    echo -e "\e[1;32msucceeded!\e[0m"
fi

