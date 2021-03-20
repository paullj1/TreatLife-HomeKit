# TreatLife HomeKit
Open source firmware with native HomeKit support, and OTA upgrades for:
* [TreatLife DS01C dimmer switch](https://smile.amazon.com/Treatlife-Incandescent-Compatible-Assistant-Single-Pole/dp/B07PJTLB7Z/ref=sr_1_1_sspa?dchild=1&keywords=treatlife+dimmer&qid=1616243705&sr=8-1)
* [TreatLife DS02S dimmer switch](https://smile.amazon.com/Treatlife-Neutral-Compatible-Assistant-Schedule/dp/B07YKFSWJN/ref=sr_1_4_sspa?dchild=1&keywords=treatlife+dimmer&qid=1615054278&sr=8-4)
* [TreatLife DS03 dimmer and fan control](https://smile.amazon.com/Ceiling-Control-Treatlife-Assistant-Schedule/dp/B086PPRWL7/ref=mp_s_a_1_1?dchild=1&keywords=treatlife+ds03&qid=1616156418&sr=8-1)

# Release Binaries
* [DS01C](https://github.com/paullj1/TreatLife-HomeKit/releases/download/v1.7/DS01C.bin)
* [DS02S](https://github.com/paullj1/TreatLife-HomeKit/releases/download/v1.7/DS02S.bin)
* [DS03](https://github.com/paullj1/TreatLife-HomeKit/releases/download/v1.7/DS03.bin)

<img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/qrcode.svg" width="150" />

# Flashing
## Using esptool from Espressif
1. Setup [esptool](https://github.com/espressif/esptool)
2. Acquire a USB to Serial adapter (I used [this one](https://www.amazon.com/dp/B07VV4B2MJ/ref=cm_sw_em_r_mt_dp_CZATT3CMYZNYN2QMV9KD?_encoding=UTF8&psc=1))
3. Solder the 3.3v (VCC), GND, TXD, and RXD onto the chip:
  * <img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/Images/Flash.jpg" width="200" />
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
* To enter config mode to change your SSID, or update the firmware, press the light on/off button 8 times with less than 1 second between presses.

# Notes
* If upgrading from tasmota, you'll need to use the gzip'd binary in the release
* This firmware is built to utilize the ESP8266EX chip in the SmartLife devices
  which has 2mb of flash
  * If upgrading from an older version, DO NOT use the gzip'd binary, the full
    bin should work

# Building
## arduino-cli
```
arduino-cli lib install WiFiManager
arduino-cli lib install HomeKit-ESP8266

# DS02S
cd DS02S
./build.sh

# DS03
cd DS03
./build.sh

# Resulting binary will be DSXXX.bin; use esptool, or Arduino to flash
```

## Arduino IDE
Use the following settings, and install the required dependencies:<br />
<img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/Images/Arduino%20Settings.png" width="200" />

# Dependencies (libraries you'll need to install in Arduino IDE):
* [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) by [Mixiaoxiao](https://github.com/Mixiaoxiao)
* [WiFi Manager](https://github.com/tzapu/WiFiManager) by [tzapu](https://github.com/tzapu)
  * Provides easy config, and OTA updates

# Credits
* Adapted Tuya MCU driver code from [Tasmota](https://tasmota.github.io/docs/)
