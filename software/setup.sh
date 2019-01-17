#!/bin/bash

#This is a script to set up the kiosk environment and software on a fresh linux install
#Tested in the Gnome version of 64-bit Debian 9.6.0: https://cdimage.debian.org/debian-cd/current-live/amd64/bt-hybrid/
#Using version 3.23 of Microchip's TSHARC drivers: https://www.microchip.com/design-centers/tsharc/software-drivers-and-driver-manuals

#The drivers for the touchscreen are 32-bit, so install i386 support
dpkg --add-architecture i386
apt-get update
apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386

#Install driver dependencies; we probably only need the i386 version, but we install both for funs
apt-get install -y libusb-0.1 libusb-0.1:i386 libx11-dev libx11-dev:i386

#Install necessary software
apt-get install -y chromium openssh-server

#Run the install script
/bin/bash ./drivers/TsharcDaemonV323.run

#Start the daemon
/etc/init.d/boot.tsharc start

#For some reason the configuration program can't create the output file on it's own, so let's help it out
touch /tmp/tsharcoutput

#Run the configuration program
hlincal

#Create script to launch browser at login

mkdir /home/kiosk/autostart
chown kiosk:kiosk /home/kiosk/autostart

PWD=`pwd`

echo \
'chromium \
    --no-first-run \
    --disable \
    --disable-translate \
    --disable-infobars \
    --disable-suggestions-service \
    --disable-save-password-bubble \
    --start-maximized \
    --kiosk \'
>/usr/bin/startkiosk
echo `pwd` > /usr/bin/startkiosk
echo  '\index.html &' > /usr/bin/startkiosk

chmod a+x /usr/bin/startkiosk

echo \
'[Desktop Entry]
Name=Kiosk
Exec=/usr/bin/startkiosk
Terminal=false
Type=Application
StartupNotify=false' \
>/home/kiosk/.config/autostart/kiosk.desktop

chown kiosk:kiosk /home/kiosk/.config/autostart/kiosk



#Disable Gnome Keyring
chmod -x $(type -p gnome-keyring-daemon)

#Disable ssh for kiosk user?

#Enable on-screen keyboard?

#Set automatic login for kiosk user

#Disable screen timeout

#Remove password for kiosk user

#Disable grub boot selection
#	/boot/grub/grub.cfg
#	set timeout to 0
