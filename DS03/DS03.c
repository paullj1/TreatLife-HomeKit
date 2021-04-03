#include "model.h"
#include "version.h"

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

// Called to identify this accessory. See HAP section 6.7.6 Identify Routine
// Generally this is called when paired successfully or click the "Identify Accessory" button in Home APP.
void my_accessory_identify(homekit_value_t _value) {
  printf("accessory identify\n");
}

char serial[16] = "XXXXXX\0";
char device_name[32] = "DS03 XXXXXX\0";

// format: bool; HAP section 9.70; bool on/off
homekit_characteristic_t cha_switch_on = HOMEKIT_CHARACTERISTIC_(ON, false);

// format: int; HAP section 9.11; brightness, value 0-100
homekit_characteristic_t cha_brightness = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 0);

// format: bool; HAP section 9.70; bool on/off
homekit_characteristic_t cha_fan_on = HOMEKIT_CHARACTERISTIC_(ACTIVE, 0);

// format: int; HAP section 9.11; brightness, value 0-100
homekit_characteristic_t cha_fan_speed = HOMEKIT_CHARACTERISTIC_(ROTATION_SPEED, 0);

homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_fan, .services=(homekit_service_t*[]) {
    HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, device_name),
      HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
      HOMEKIT_CHARACTERISTIC(MANUFACTURER, ROBO_MANUFACTURER),
      HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, serial),
      HOMEKIT_CHARACTERISTIC(MODEL, ROBO_MODEL),
      HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, ROBO_VERSION),
      NULL
    }),
    // HAP section 8.13; Req 9.3 (Active) pg 159; Optional: 9.81 Speed pg 197
    HOMEKIT_SERVICE(FAN2, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Fan"),
      &cha_fan_on,
      &cha_fan_speed,
      NULL
    }),
    // HAP section 8.23
    HOMEKIT_SERVICE(LIGHTBULB, .primary=false, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Dimmer"),
      &cha_switch_on,
      &cha_brightness,
      NULL
    }),
    NULL
  }),
  NULL
};

homekit_server_config_t config = {
  .accessories = accessories,
  .password = ROBO_SETUP_CODE,
};
