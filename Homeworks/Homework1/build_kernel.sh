#!/bin/bash

echo "Starting the kernel compilation"

#Install the required packages if not installed
ldconfig -p | grep libelf
if [$? -eq 1]; then
	sudo apt-get install libelf-dev

ldconfig -p | grep ncurses
if [$? -eq 1]; then
	sudo apt-get install libncurses5-dev

#do menuconfig
make menuconfig

#default build using make and send the output to log file
make -j4 > kernel-build.log

#Also make modules and make modules_install and put the output in the log file
sudo make modules >> kernel-build.log
sudo make modules_install >> kernel-build.log

echo "Kernel Compilation done"
