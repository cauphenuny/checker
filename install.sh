#!/bin/sh
if [ ! $(command -v wget) ]; then
    echo "please install wget"
    exit 0
fi

if [ -f  /bin/checker ]; then
    echo "Warning: remove /bin/checker"
    sudo rm /bin/checker
fi
if [ -f  /usr/bin/checker ]; then
    echo "Warning: remove /usr/bin/checker"
    sudo rm /usr/bin/checker
fi
if [ -f  /usr/local/bin/checker ]; then
    echo "Warning: remove /usr/local/bin/checker"
    sudo rm /usr/local/bin/checker
fi
if [ -f /tmp/checker/source ]; then
    rm -rf /tmp/checker/source
fi

echo "download file ..."
rm -rf /tmp/checker/source/
mkdir -p /tmp/checker/source/
cp -r ./ /tmp/checker/source/
cd /tmp/checker/source/

echo "copy file ..."
sudo sh ./copy.sh
sudo chmod 777 /usr/local/bin/checker
mkdir -p /tmp/checker/update
cp /tmp/checker/source/update.sh /tmp/checker/update/update.sh
sudo chmod 777 /tmp/checker/update/update.sh
