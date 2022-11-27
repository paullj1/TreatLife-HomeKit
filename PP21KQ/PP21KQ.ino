#include "includes.h"
#include <math.h>

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
  uint8_t value = 0;
  uint16_t level = 0;

  uint16_t dpDataLen  = Tuya.buffer[dpidStart + 2] << 8 | Tuya.buffer[dpidStart + 3];
  uint8_t  dpId       = Tuya.buffer[dpidStart];
  uint8_t  dpDataType = Tuya.buffer[dpidStart + 1];

  switch (dpId) {

    case A_ON_ID:
      cha_side_a_on.value.bool_value = (Tuya.buffer[dpidStart + 4] == 0x01) ? true : false;
      homekit_characteristic_notify(&cha_side_a_on, cha_side_a_on.value);
      break;

    case B_ON_ID:
      cha_side_b_on.value.bool_value = (Tuya.buffer[dpidStart + 4] == 0x01) ? true : false;
      homekit_characteristic_notify(&cha_side_b_on, cha_side_b_on.value);
      break;

    case A_LEVEL_ID:
      value = Tuya.buffer[dpidStart + 4];
      level = (value * 10) + 10;
      cha_side_a_level.value.int_value = level;
      homekit_characteristic_notify(&cha_side_a_level, cha_side_a_level.value);
      break;

    case B_LEVEL_ID:
      value = Tuya.buffer[dpidStart + 4];
      level = (value * 10) + 10;
      cha_side_b_level.value.int_value = level;
      homekit_characteristic_notify(&cha_side_b_level, cha_side_b_level.value);
      break;

    case A_PREHEAT_ID:
      cha_side_a_preheat.value.bool_value = (Tuya.buffer[dpidStart + 4] == 0x01) ? true : false;
      homekit_characteristic_notify(&cha_side_a_preheat, cha_side_a_preheat.value);
      break;

    case B_PREHEAT_ID:
      cha_side_b_preheat.value.bool_value = (Tuya.buffer[dpidStart + 4] == 0x01) ? true : false;
      homekit_characteristic_notify(&cha_side_b_preheat, cha_side_b_preheat.value);
      break;

  }
}

void identify() {
  tuya_send_bool(A_ON_ID, true);
  delay(1);
  tuya_send_bool(A_ON_ID, false);
  delay(1);
  tuya_send_bool(A_ON_ID, true);
  delay(1);
  tuya_send_bool(A_ON_ID, false);
}


// ---------------------------------------------------------
// HOMEKIT Stuff
// ---------------------------------------------------------

void homekit_setup() {
  sprintf(serial, "R0B0%X\0", ESP.getChipId());
  sprintf(device_name, "%s %X\0", ROBO_MODEL, ESP.getChipId());

  cha_side_a_on.setter = cha_side_a_on_setter;
  cha_side_b_on.setter = cha_side_b_on_setter;
  cha_side_a_preheat.setter = cha_side_a_preheat_setter;
  cha_side_b_preheat.setter = cha_side_b_preheat_setter;
  cha_side_a_level.setter = cha_side_a_value_setter;
  cha_side_b_level.setter = cha_side_b_value_setter;

  arduino_homekit_setup(&config);
}

void cha_side_a_on_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_side_a_on.value.bool_value = on;  //sync the value
  tuya_send_bool(A_ON_ID, on);
}

void cha_side_b_on_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_side_b_on.value.bool_value = on;  //sync the value
  tuya_send_bool(B_ON_ID, on);
}

void cha_side_a_preheat_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_side_a_on.value.bool_value = on;  //sync the value
  tuya_send_bool(A_PREHEAT_ID, on);
}

void cha_side_b_preheat_setter(const homekit_value_t value) {
  bool on = value.bool_value;
  cha_side_b_on.value.bool_value = on;  //sync the value
  tuya_send_bool(B_PREHEAT_ID, on);
}

void cha_side_a_value_setter(const homekit_value_t value) {
  uint16_t level = (uint16_t) round(value.int_value / 10);
  if (level > 0) {
    level--;
  }
  cha_side_a_level.value.int_value = level;  //sync the value
  tuya_send_enum(A_LEVEL_ID, level);
}

void cha_side_b_value_setter(const homekit_value_t value) {
  uint16_t level = (uint16_t) round(value.int_value / 10);
  if (level > 0) {
    level--;
  }
  cha_side_b_level.value.int_value = level;  //sync the value
  tuya_send_enum(B_LEVEL_ID, level);
}
