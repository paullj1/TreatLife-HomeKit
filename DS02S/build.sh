#!/bin/bash

arduino-cli compile --fqbn esp8266:esp8266:generic:xtal=160,vt=flash,exception=disabled,ResetMethod=nodemcu,CrystalFreq=26,FlashFreq=40,FlashMode=dout,eesz=2M,led=2,ip=lm2f,dbg=Disabled,lvl=None____,wipe=none,baud=115200 --libraries ~/Documents/Arduino/libraries/ -e ./

mv ./build/esp8266.esp8266.generic/DS02S.ino.bin ./DS02S.bin
rm -rf ./build
