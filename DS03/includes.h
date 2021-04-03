#include <arduino_homekit_server.h>
#include <WiFiManager.h>

#include "tuya.h"
#include "model.h"

#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG

#define FAN_ON_ID              0x01
#define FAN_SPEED_ID           0x03
#define DIMMER_ON_ID           0x09
#define DIMMER_VALUE_ID        0x0a
#define FAN_TIMER_ID           0x65
#define DIMMER_TIMER_ID        0x67
#define DIMMER_MINIMUM_ID      0x69
#define DIMMER_TYPE_ID         0x6a

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;
extern "C" homekit_characteristic_t cha_fan_on;
extern "C" homekit_characteristic_t cha_fan_speed;

extern "C" char serial[16];
extern "C" char device_name[32];
