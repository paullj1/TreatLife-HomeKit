#include "includes.h"

void setup() {  
  WiFi.mode(WIFI_STA);

  tuya_init(115200);
  tuya_set_wifi(TUYA_WIFI_DISCONNECTED);

  WiFiManager wm;
  wm.setDebugOutput(false);
  wm.setConfigPortalTimeout(WIFI_BOOT_CONFIG_TIMEOUT);
  if (!wm.autoConnect()) {
    ESP.restart();
  }
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
  uint8_t speed = 0;
  uint32_t level = 0;


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

    case FAN_ON_ID:
      cha_fan_on.value.uint8_value = Tuya.buffer[dpidStart + 4];
      homekit_characteristic_notify(&cha_fan_on, cha_fan_on.value);
      break;

    case FAN_SPEED_ID:
      speed = Tuya.buffer[dpidStart + 4];
      level = 0;

      switch (speed) {
        case 0:
          level = 25;
          break;
        case 1:
          level = 50;
          break;
        case 2:
          level = 75;
          break;
        case 3:
          level = 100;
          break;
      }
  
      cha_fan_speed.value.float_value = level;
      homekit_characteristic_notify(&cha_fan_speed, cha_fan_speed.value);
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

void identify() {
  tuya_send_bool(DIMMER_ON_ID, true);
  tuya_send_value(DIMMER_VALUE_ID, 0);
  for (uint32_t i = 0; i < 1000; i += 10) {
    tuya_send_value(DIMMER_VALUE_ID, i);
    delay(5);
  }
  for (uint32_t i = 1000; i > 0; i -= 10) {
    tuya_send_value(DIMMER_VALUE_ID, i);
    delay(5);
  }
  tuya_send_bool(DIMMER_ON_ID, false);
}


// ---------------------------------------------------------
// HOMEKIT Stuff
// ---------------------------------------------------------

void homekit_setup() {
  sprintf(serial, "R0B0%X\0", ESP.getChipId());
  sprintf(device_name, "DS03 %X\0", ESP.getChipId());

  cha_switch_on.setter = cha_switch_on_setter;
  cha_brightness.setter = cha_switch_brightness_setter;
  cha_fan_on.setter = cha_fan_on_setter;
  cha_fan_speed.setter = cha_fan_speed_setter;
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

void cha_fan_on_setter(const homekit_value_t value) {
  int on = value.uint8_value;
  cha_fan_on.value.uint8_value = on;  //sync the value
  tuya_send_bool(FAN_ON_ID, (on == 1) ? true : false);
}

void cha_fan_speed_setter(const homekit_value_t value) {
  uint32_t speed = 0;
  int level = value.float_value;
  cha_fan_speed.value.float_value = level;  //sync the value

  if (level <= 37) {
    speed = 0;
    level = 25;
  } else if (level > 37 && level <= 62) {
    speed = 1;
    level = 50;
  } else if (level > 62 && level <= 87) {
    speed = 2;
    level = 75;
  } else if (level > 87) {
    speed = 3;
    level = 100;
  }
  tuya_send_enum(FAN_SPEED_ID, speed);
}
