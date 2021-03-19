# TreatLife HomeKit
Open source firmware with native HomeKit support, and OTA upgrades for:
* [TreatLife DS02S dimmer switch](https://smile.amazon.com/Treatlife-Neutral-Compatible-Assistant-Schedule/dp/B07YKFSWJN/ref=sr_1_4_sspa?dchild=1&keywords=treatlife+dimmer&qid=1615054278&sr=8-4-spons)
* [TreatLife DS03 dimmer and fan control](https://smile.amazon.com/Ceiling-Control-Treatlife-Assistant-Schedule/dp/B086PPRWL7/ref=mp_s_a_1_1?dchild=1&keywords=treatlife+ds03&qid=1616156418&sr=8-1)

<img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/qrcode.svg" width="150" />

# Notes
* To enter WiFi config mode to do OTA update, press the on/off button 8 times with less than 1 second between presses
* Setup code is 030-52-021
* Communicates with Tuya MCU to control devices
* If upgrading from tasmota, you'll need to gzip the firmware file before uploading it
  * NOTE: Tasmota expects a gzip file, not a tar.gz, just run `gzip DS02S.bin`
* This firmware is built to utilize the ESP8266EX chip in the SmartLife devices which has 2mb of flash
  * Upgrading does not require gzip'ing the firmware

# Building
## arduino-cli
```
arduino-cli lib install WiFiManager
arduino-cli lib install HomeKit-ESP8266
./build.sh
```

## Arduino IDE
Use the following settings, and install the required dependencies:
<img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/Images/Arduino%20Settings.png" width="200" />

## Flashing
<img src="https://github.com/paullj1/TreatLife-DS02S-HomeKit/raw/main/Images/Flash.jpg" width="200" />
NOTE: You'll need to pull GPIO3 to ground when you power it on. The DS03 has the same chip, and is flashed the same way

# Dependencies (libraries you'll need to install in Arduino IDE):
* [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) by [Mixiaoxiao](https://github.com/Mixiaoxiao)
* [WiFi Manager](https://github.com/tzapu/WiFiManager) by [tzapu](https://github.com/tzapu)
  * Provides easy config, and OTA updates

# Credits
* Adapted Tuya MCU driver code from [Tasmota](https://tasmota.github.io/docs/)
