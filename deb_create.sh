#!/bin/bash

################################################################################

APP_NAME=osgAssembler
APP_VER=0.1

################################################################################

APP_DIR=${APP_NAME}_${APP_VER}_focal_amd64

sudo rm -R $APP_DIR
sudo rm $APP_DIR.deb

mkdir $APP_DIR
mkdir $APP_DIR/DEBIAN
mkdir $APP_DIR/usr
mkdir $APP_DIR/usr/bin
mkdir $APP_DIR/usr/share
mkdir $APP_DIR/usr/share/applications
mkdir $APP_DIR/usr/share/icons
mkdir $APP_DIR/usr/share/icons/hicolor
mkdir $APP_DIR/usr/share/icons/hicolor/128x128
mkdir $APP_DIR/usr/share/icons/hicolor/128x128/apps

cp deb_osgAssembler_amd64.control $APP_DIR/DEBIAN/control

cp bin/osgAssembler $APP_DIR/usr/bin/

cp osgAssembler.desktop $APP_DIR/usr/share/applications/

cp osgAssembler.png $APP_DIR/usr/share/icons/hicolor/128x128/apps/

sudo chown root:root -R $APP_DIR
sudo chmod 0755 $APP_DIR/usr/bin/osgAssembler
sudo chmod 0755 $APP_DIR/usr/share/applications/osgAssembler.desktop
sudo chmod 0755 $APP_DIR/usr/share/icons/hicolor/128x128/apps/osgAssembler.png

dpkg -b $APP_DIR/

################################################################################

read -p "Press any key to continue..." -n1 -s
