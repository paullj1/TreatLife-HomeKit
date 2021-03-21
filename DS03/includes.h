#include <arduino_homekit_server.h>
#include <WiFiManager.h>

#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG

#define TUYA_BUFFER_SIZE 256
#define CONFIG_MODE_PRESS_COUNT 8
#define CONFIG_MODE_TIMEOUT 1000 // milliseconds per press
#define WIFI_BOOT_CONFIG_TIMEOUT 20

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

#define TUYA_WIFI_DISCONNECTED 0x02
#define TUYA_WIFI_CONNECTED    0x03

#define TUYA_TYPE_BOOL         0x01
#define TUYA_TYPE_VALUE        0x02
#define TUYA_TYPE_STRING       0x03
#define TUYA_TYPE_ENUM         0x04

#define FAN_ON_ID              0x01
#define FAN_SPEED_ID           0x03
#define DIMMER_ON_ID           0x09
#define DIMMER_VALUE_ID        0x0a

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;
extern "C" homekit_characteristic_t cha_fan_on;
extern "C" homekit_characteristic_t cha_fan_speed;

extern "C" char serial[16];
extern "C" char device_name[32];
