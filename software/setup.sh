#!/bin/bash

#This is a script to set up the kiosk environment and software on a fresh linux install
#Tested in the Gnome version of 64-bit Debian 9.6.0: https://cdimage.debian.org/debian-cd/current-live/amd64/bt-hybrid/
#Using version 3.23 of Microchip's TSHARC drivers: https://www.microchip.com/design-centers/tsharc/software-drivers-and-driver-manuals

#The drivers for the touchscreen are 32-bit, so install i386 support
dpkg --add-architecture i386
apt-get update
apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386

#Install driver dependencies; we probably only need the i386 version, but we install both for funs
apt-get install libusb-0.1
apt-get install libusb-0.1:i386
apt-get install libx11-dev
apt-get install libx11-dev:i386

#Run the install script
/bin/bash ./drivers/TsharcDaemonV323.run

#Start the daemon
/etc/init.d/boot.tsharc start

#For some reason the configuration program can't create the output file on it's own, so let's help it out
touch /tmp/tsharcoutput

#Run the configuration program
hlincal




