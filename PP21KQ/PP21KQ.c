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
char device_name[32] = "PP21KQ XXXXXX\0";

// format: bool; HAP section 9.70; write the .setter function to get the switch-event sent from iOS Home APP.
homekit_characteristic_t cha_side_a_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_side_b_on = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_side_a_preheat = HOMEKIT_CHARACTERISTIC_(ON, false);
homekit_characteristic_t cha_side_b_preheat = HOMEKIT_CHARACTERISTIC_(ON, false);

// format: int; HAP section 9.11; brightness, value 0-100
homekit_characteristic_t cha_side_a_level = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 0);
homekit_characteristic_t cha_side_b_level = HOMEKIT_CHARACTERISTIC_(BRIGHTNESS, 0);

homekit_accessory_t *accessories[] = {
  HOMEKIT_ACCESSORY(.id=1, .category=homekit_accessory_category_other, .services=(homekit_service_t*[]) {
    HOMEKIT_SERVICE(ACCESSORY_INFORMATION, .characteristics=(homekit_characteristic_t*[]) {
            HOMEKIT_CHARACTERISTIC(NAME, device_name),
            HOMEKIT_CHARACTERISTIC(IDENTIFY, my_accessory_identify),
            HOMEKIT_CHARACTERISTIC(MANUFACTURER, ROBO_MANUFACTURER),
            HOMEKIT_CHARACTERISTIC(SERIAL_NUMBER, serial),
            HOMEKIT_CHARACTERISTIC(MODEL, ROBO_MODEL),
            HOMEKIT_CHARACTERISTIC(FIRMWARE_REVISION, ROBO_VERSION),
      NULL
    }),
    HOMEKIT_SERVICE(LIGHTBULB, .primary=false, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Side A"),
      &cha_side_a_on,
      &cha_side_a_level,
      NULL
    }),
    HOMEKIT_SERVICE(SWITCH, .primary=false, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Side A Preheat"),
      &cha_side_a_preheat,
      NULL
    }),
    HOMEKIT_SERVICE(LIGHTBULB, .primary=false, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Side B"),
      &cha_side_b_on,
      &cha_side_b_level,
      NULL
    }),
    HOMEKIT_SERVICE(SWITCH, .primary=false, .characteristics=(homekit_characteristic_t*[]) {
      HOMEKIT_CHARACTERISTIC(NAME, "Side B Preheat"),
      &cha_side_b_preheat,
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
