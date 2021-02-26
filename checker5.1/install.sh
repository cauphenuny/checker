#!/bin/bash
if ! [ -f ./checker ]; then
    bash ./compile.sh
fi
if [ -f /usr/local/bin/checker ]; then
    rm /usr/local/bin/checker
fi
cp checker /bin/checker
chmod 777 /bin/checker

