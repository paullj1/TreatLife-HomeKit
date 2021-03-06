# TreatLife-DS02S-HomeKit
Open source firmware for the [TreatLife DS02S dimmer switch](https://smile.amazon.com/Treatlife-Neutral-Compatible-Assistant-Schedule/dp/B07YKFSWJN/ref=sr_1_4_sspa?dchild=1&keywords=treatlife+dimmer&qid=1615054278&sr=8-4-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFaWVA5RTM2WFZXUUgmZW5jcnlwdGVkSWQ9QTA0NTA1ODQyT0lJWTNBMkdQUzFRJmVuY3J5cHRlZEFkSWQ9QTA4NzE4MjhIRjBMOVo1N1Q5SUwmd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl)  for native HomeKit use.

# Notes
* To enter WiFi config mode to do OTA update, press the on/off button 8 times with less than 1 second between presses
* Setup code was the date I built final image:  030-52-021
* Communicates with Tuya MCU to control dimmer
* Mostly hard-coded to work with the DS02S, but code can be modified to talk to other Tuya MCU devices
* If upgrading from tasmota, use the gzip'd `dimmer_v1.4.bin.gz`
* If upgrading from this firmware, gunzip the `minimal.bin.gz`, enter config mode, and do an OTA update to that.  After minimal boots, gunzip `dimmer_v1.4.bin.gz`, and perform OTA update with resulting .bin file.

# Dependencies (libraries you'll need to install in Arduino IDE):
* [Arduino-HomeKit-ESP8266](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266) by [Mixiaoxiao](https://github.com/Mixiaoxiao)
* [WiFi Manager](https://github.com/tzapu/WiFiManager) by [tzapu](https://github.com/tzapu)
  * Provides easy config, and OTA updates

# Credits
* Adapted Tuya MCU driver code from [Tasmota](https://tasmota.github.io/docs/)
