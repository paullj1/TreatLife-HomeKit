#include "includes.h"

void setup() {  
  tuya_init(9600);
  tuya_set_wifi(TUYA_WIFI_DISCONNECTED);

  WiFiManager wm;
  wm.setDebugOutput(false);
  wm.setConfigPortalTimeout(WIFI_BOOT_CONFIG_TIMEOUT);
  if (!wm.autoConnect()) {
    ESP.restart();
  }
  WiFi.mode(WIFI_STA);
  tuya_set_wifi(TUYA_WIFI_CONNECTED);

  homekit_setup();
}

void loop() {
  arduino_homekit_loop();
  tuya_loop();
}

void tuya_process_state_packet() {

  uint8_t dpidStart = 6;
  bool PowerOff = false;
  uint16_t val = 0;

  uint16_t dpDataLen  = Tuya.buffer[dpidStart + 2] << 8 | Tuya.buffer[dpidStart + 3];
  uint8_t  dpId       = Tuya.buffer[dpidStart];
  uint8_t  dpDataType = Tuya.buffer[dpidStart + 1];

  switch (dpId) {

    case DIMMER_ON_ID:
      cha_switch_on.value.bool_value = (Tuya.buffer[dpidStart + 4] == 0x01) ? true : false;
      homekit_characteristic_notify(&cha_switch_on, cha_switch_on.value);
      break;

    case DIMMER_VALUE_ID:
      val = Tuya.buffer[dpidStart + 6] << 8  |
            Tuya.buffer[dpidStart + 7];

      cha_brightness.value.int_value = (val / 10);
      homekit_characteristic_notify(&cha_brightness, cha_brightness.value);
      break;

    case DIMMER_MINIMUM_ID:
      val = Tuya.buffer[dpidStart + 6] << 8  |
            Tuya.buffer[dpidStart + 7];

      if (val == 100) { // indicates default value
        tuya_send_value(DIMMER_MINIMUM_ID, MINIMUM_DIMMER_VALUE);
      }
      break;
  }
}

// ---------------------------------------------------------
// HOMEKIT Stuff
// ---------------------------------------------------------

void homekit_setup() {
  sprintf(serial, "R0B0%X\0", ESP.getChipId());
  sprintf(device_name, "%s %X\0", ROBO_MODEL, ESP.getChipId());

  cha_switch_on.setter = cha_switch_on_setter;
  cha_brightness.setter = cha_switch_brightness_setter;
  arduino_homekit_setup(&config);
}

void cha_switch_on_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_switch_on.value.bool_value = on;  //sync the value
  tuya_send_bool(DIMMER_ON_ID, on);
}

void cha_switch_brightness_setter(const homekit_value_t value) {
  int level = value.int_value;
  cha_brightness.value.int_value = level;  //sync the value
  uint16_t scaled_level = level * 10;
  tuya_send_value(DIMMER_VALUE_ID, scaled_level);
}
