#include "model.h"
#include "version.h"

#include <homekit/homekit.h>
#include <homekit/characteristics.h>

// Called to identify this accessory. See HAP section 6.7.6 Identify Routine
// Generally this is called when paired successfully or click the "Identify Accessory" button in Home APP.
void my_accessory_identify(homekit_value_t _value) {
  identify();
}

char serial[16] = "XXXXXX\0";
char device_name[32] = "XXXXXX\0";

// format: bool; HAP section 9.70; write the .setter function to get the switch-event sent from iOS Home APP.
homekit_characteristic_t cha_switch_on = HOMEKIT_CHARACTERISTIC_(ON, false);

// format: string; HAP section 9.62; max length 64

// format: int; HAP section 9.11; brightness, value 0-100
homekit_characteristic_t cha_brightness = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 0);

homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_lightbulb, .services=(homekit_service_t*[]) {
    HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, device_name),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, ROBO_MANUFACTURER),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, serial),
            HOMEKIT_CHARACTERISTIC(MODEL, ROBO_MODEL),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, ROBO_VERSION),
      NULL
    }),
    HOMEKIT_SERVICE(LIGHTBULB, .primary=true, .characteristics=(homekit_characteristic_t*[]) {
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
