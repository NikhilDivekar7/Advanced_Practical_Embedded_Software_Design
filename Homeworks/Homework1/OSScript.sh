#!/bin/bash

echo -e "User Information : $USER \n" > OSInfo.txt
echo -e "OS Type : $OSTYPE \n" >> OSInfo.txt
echo -e "$(lsb_release -i)\n" >> OSInfo.txt
echo -e "OS Version: $(lsb_release -r)\n" >> OSInfo.txt
echo -e "Kernel Version : $(uname -r)\n" >> OSInfo.txt
echo -e "GCC Build Version: $(gcc --version)\n" >> OSInfo.txt
echo -e "Kernel build time: $(uname -v)\n" >> OSInfo.txt
echo -e "System Architecture : $(uname -i)\n" >>OSInfo.txt
echo -e "File System Memory: $(free -m)\n" >> OSInfo.txt
