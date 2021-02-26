#!/bin/sh
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
if [ -f ~/.ycpedef_checker_source ]; then
    rm -rf ~/.ycpedef_checker_source
fi

echo "installing dependencies ..."
sudo apt install -y git wget vim 1>/dev/null 2>/dev/null

echo "download file ..."
rm -rf ~/.ycpedef_checker_source/
mkdir -p ~/.ycpedef_checker_source/
cp -r ./ ~/.ycpedef_checker_source/
cd ~/.ycpedef_checker_source/

echo "copy file ..."
sudo sh ./copy.sh
sudo chmod 777 /usr/local/bin/checker
mkdir -p ~/.ycpedef_checker_update
cp ~/.ycpedef_checker_source/auto_update.sh ~/.ycpedef_checker_update/auto_update.sh
cp ~/.ycpedef_checker_source/forced_update.sh ~/.ycpedef_checker_update/forced_update.sh
sudo chmod 777 ~/.ycpedef_checker_update/auto_update.sh
sudo chmod 777 ~/.ycpedef_checker_update/forced_update.sh
