# TreatLife HomeKit
Open source firmware with native HomeKit support, and OTA upgrades for:
* [TreatLife DS01C touch dimmer switch](https://smile.amazon.com/dp/B07PJTLB7Z)
* [TreatLife DS02S dimmer switch](https://smile.amazon.com/dp/B07YKFSWJN)
* [TreatLife DS02 three-way dimmer switch](https://smile.amazon.com/dp/B08R89VNMV)
* [TreatLife DS03 dimmer and fan control](https://smile.amazon.com/dp/B086PPRWL7)

# Release Binaries
[![Github All Releases](https://img.shields.io/github/downloads/paullj1/TreatLife-HomeKit/total.svg)]()
[![Latest](https://img.shields.io/github/v/tag/paullj1/TreatLife-HomeKit?color=Blue&label=last+release)](https://github.com/paullj1/TreatLife-HomeKit/releases)
* [DS01C](https://github.com/paullj1/TreatLife-HomeKit/releases/latest/download/DS01C.bin)
* [DS02](https://github.com/paullj1/TreatLife-HomeKit/releases/latest/download/DS02.bin)
* [DS02S](https://github.com/paullj1/TreatLife-HomeKit/releases/latest/download/DS02S.bin)
* [DS03](https://github.com/paullj1/TreatLife-HomeKit/releases/latest/download/DS03.bin)

<img src="https://github.com/paullj1/TreatLife-HomeKit/raw/main/qrcode.svg" width="150" />

# Flashing
## Using esptool from Espressif
1. Setup [esptool](https://github.com/espressif/esptool)
2. Acquire a USB to Serial adapter (I used [this one](https://www.amazon.com/dp/B07VV4B2MJ))
3. Solder the 3.3v (VCC), GND, TXD, and RXD onto the chip:
  * <img src="https://github.com/paullj1/TreatLife-HomeKit/raw/main/Images/Flash.jpg" width="200" />
4. Connect GPIO0 to ground when applying power to the chip to enter flash mode
  * I did this by soldering a wire to the back of the USB to serial adapter's GND pin, and then touching it to GPIO0 when plugging in USB adapter
5. Run esptool (where `/dev/tty.usbserial-XXXX` is your USB to serial adapter, and `DS02S.bin` is the desired firmware image):
```
esptool.py -p /dev/tty.usbserial-XXXX -b 115200 write_flash -e 0x0 DS02S.bin
```
6. Reboot device by unplugging USB power, and then plugging it back in

# Setup
1. When device boots, it will enter config mode
2. Connect to WiFi access point the device exposes (ESP-XXXXXX) where XXXXXX is the last 6 bytes of the devices MAC address
3. Configure your WiFi SSID/password
4. Go to the home app on your iPhone/iPad and press the "+" button and select "Add Accessory"
5. Press "I Don't Have a Code or Cannot Scan"
6. Your device should appear on this screen, select it, and enter the setup code "030-52-021" (or use QR code above)
7. Device should pair

# Config Mode
* To enter config mode to change your SSID, or update the firmware, press and hold the light on/off button for at least five seconds, then browse to the IP address of the device.  To get the IP, you can look at your ARP cache for the MAC address which matches the devices serial number. 

# Notes
* If upgrading from tasmota, you'll need to use the gzip'd binary in the release
* This firmware is built to utilize the ESP8266EX chip in the SmartLife devices
  which has 2mb of flash
  * If upgrading from an older version, DO NOT use the gzip'd binary, the full
    bin should work

# Building
## arduino-cli
```
# To build a specific device, cd into its dir, then:
# In any of the device directories (DS01C, DS02S, DS03, etc...)
make requirements
make compile
# Resulting binary will be DSXXX.bin; use esptool, "make upload", or Arduino to flash

# To build all at once from top level directory (resulting bins will be in 'release' dir):
make
```

## Arduino IDE
Use the following settings, and install the required dependencies:<br />
<img src="https://github.com/paullj1/TreatLife-HomeKit/raw/main/Images/Arduino%20Settings.png" width="200" />

# Dependencies (libraries you'll need to install in Arduino IDE):
* [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) by [Mixiaoxiao](https://github.com/Mixiaoxiao)
* [WiFi Manager](https://github.com/tzapu/WiFiManager) by [tzapu](https://github.com/tzapu)
  * Provides easy config, and OTA updates

# Credits
* Adapted Tuya MCU driver code from [Tasmota](https://tasmota.github.io/docs/)
