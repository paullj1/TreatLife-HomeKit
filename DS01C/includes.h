
#define WM_FIXERASECONFIG

#ifdef _DEBUG_TUYA
#define WM_DEBUG_LEVEL 3
#define HOMEKIT_LOG_LEVEL 3
#else
#define WM_DEBUG_LEVEL 0
#define HOMEKIT_LOG_LEVEL 0
#endif

#include <WiFiManager.h>
#include <arduino_homekit_server.h>

#include "tuya.h"
#include "model.h"

#define DIMMER_ON_ID           0x01
#define DIMMER_VALUE_ID        0x02
#define DIMMER_MINIMUM_ID      0x03

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;

extern "C" char serial[16];
extern "C" char device_name[32];
extern "C" void identify();
