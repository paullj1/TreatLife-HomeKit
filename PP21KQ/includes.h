#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG
#define USEOTA

#include <WiFiManager.h>
#include <arduino_homekit_server.h>

#include "tuya.h"
#include "model.h"

#define ALL_ON_ID       0x1   // All On/Off (bool)
#define ALL_LEVEL_ID    0x4   // All Level (enum; 0-9)
#define ALL_PREHEAT_ID  0x8   // All Preheat (bool)
#define A_ON_ID         0xE   // A On/Off (bool)
#define B_ON_ID         0xF   // B On/Off (bool)
#define A_LEVEL_ID      0x14  // A Level (enum; 0-9)
#define B_LEVEL_ID      0x15  // B Level (enum; 0-9)
#define A_PREHEAT_ID    0x18  // A Preheat (bool)
#define B_PREHEAT_ID    0x19  // B Preheat (bool)
/*
 * 0x1a Unknown Enum, 0-13 (seem to be related to auto-off timer A)
 * 0x1b Unknown Enum, 0-13 (seem to be related to auto-off timer B)
 * 0x1c Integer, 36000 default (auto-off timer A)
 * 0x1d Integer, 36000 default (auto-off timer B)
 * 0x66 Integer, 1800 default (Pre-heat timer A; read only)
 * 0x67 Integer, 1800 default (Pre-heat timer B; read only)
 * 0x68 Enum, 1 = unconfirmed presence; 0 = confirmed (read only)
 * 0x69 Unknown Enum, default 2
 *
 */

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_side_a_on;
extern "C" homekit_characteristic_t cha_side_b_on;
extern "C" homekit_characteristic_t cha_side_a_level;
extern "C" homekit_characteristic_t cha_side_b_level;
extern "C" homekit_characteristic_t cha_side_a_preheat;
extern "C" homekit_characteristic_t cha_side_b_preheat;

extern "C" char serial[16];
extern "C" char device_name[32];
extern "C" void identify();
