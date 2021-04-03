#include <WiFiManager.h>
#include <arduino_homekit_server.h>

#include "tuya.h"
#include "model.h"

#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG

#define DIMMER_ON_ID           0x01
#define DIMMER_VALUE_ID        0x02
#define DIMMER_MINIMUM_ID      0x03  // Does not appear to work on the DS02
#define DIMMER_TYPE_ID         0x04  // Not used; different dimmer types (0,1,2)
#define DIMMER_TIMER           0x66  // Not used; 0-1000

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;

extern "C" char serial[16];
extern "C" char device_name[32];
