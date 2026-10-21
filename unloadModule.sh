#!/bin/bash

MODULE_NAME=$1

sudo rmmod -f $MODULE_NAME
echo "Deleted device file"


sudo rm -f /dev/$MODULE_NAME
echo "Unloaded the module"


make clean
