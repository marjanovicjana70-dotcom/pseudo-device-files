#!/bin/bash

MODULE_NAME="byteDump"

sudo rm -f /dev/$MODULE_NAME
sudo rmmod byteDump 


make
sudo insmod byteDump.ko

MAJOR_NUM=$(cat /proc/devices | grep byteDump | cut -c 1-3)

sudo mknod /dev/$MODULE_NAME c $MAJOR_NUM 0
sudo chmod 666 /dev/$MODULE_NAME
