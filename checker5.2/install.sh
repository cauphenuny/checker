#!/bin/bash
if ! [ -f ./checker ]; then
    bash ./compile.sh
fi
cp checker /bin/checker
chmod 777 /bin/checker

