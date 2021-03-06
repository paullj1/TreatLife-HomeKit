#include <WiFiManager.h>
#include <arduino_homekit_server.h>

#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG

#define MSG_BRIGHTNESS 8
#define MSG_SWITCH     5
#define MSG_HEARTBEAT  1

#define TUYA_BUFFER_SIZE 256
#define CONFIG_MODE_PRESS_COUNT 8
#define CONFIG_MODE_TIMEOUT 1000 // milliseconds per press

#define TUYA_CMD_HEARTBEAT     0x00
#define TUYA_CMD_QUERY_PRODUCT 0x01
#define TUYA_CMD_MCU_CONF      0x02
#define TUYA_CMD_WIFI_STATE    0x03
#define TUYA_CMD_WIFI_RESET    0x04
#define TUYA_CMD_WIFI_SELECT   0x05
#define TUYA_CMD_SET_DP        0x06
#define TUYA_CMD_STATE         0x07
#define TUYA_CMD_QUERY_STATE   0x08
#define TUYA_CMD_SET_TIME      0x1C

#define TUYA_TYPE_BOOL         0x01
#define TUYA_TYPE_VALUE        0x02
#define TUYA_TYPE_STRING       0x03
#define TUYA_TYPE_ENUM         0x04

#define DIMMER_ON_ID           0x01
#define DIMMER_VALUE_ID        0x02
#define DIMMER_MIN_ID          0x03

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;
extern "C" char serial[16];
extern "C" char device_name[32];
