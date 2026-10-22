#!/bin/bash

sudo rm -f /dev/byteDump
sudo rmmod byteDump 

sudo rm -f /dev/spamZero
sudo rmmod spamZero 


make
sudo insmod byteDump.ko
sudo insmod spamZero.ko


MAJOR_NUM=$(cat /proc/devices | grep byteDump | cut -c 1-3)

sudo mknod /dev/byteDump c $MAJOR_NUM 0
sudo mknod /dev/spamZero c $MAJOR_NUM 1

sudo chmod 666 /dev/byteDump
sudo chmod 666 /dev/spamZero
