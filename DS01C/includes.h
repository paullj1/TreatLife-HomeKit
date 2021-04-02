#include <WiFiManager.h>
#include <arduino_homekit_server.h>

#define WM_DEBUG_LEVEL DEBUG_ERROR
#define HOMEKIT_LOG_LEVEL HOMEKIT_NO_LOG

#define TUYA_BUFFER_SIZE         256
#define WIFI_BOOT_CONFIG_TIMEOUT  20
#define MINIMUM_DIMMER_VALUE      10

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

#define TUYA_WIFI_CONFIG_MODE  0x01
#define TUYA_WIFI_DISCONNECTED 0x02
#define TUYA_WIFI_CONNECTED    0x03

#define TUYA_TYPE_BOOL         0x01
#define TUYA_TYPE_VALUE        0x02
#define TUYA_TYPE_STRING       0x03
#define TUYA_TYPE_ENUM         0x04

#define DIMMER_ON_ID           0x01
#define DIMMER_VALUE_ID        0x02
#define DIMMER_MINIMUM_ID      0x03

extern "C" homekit_server_config_t config;
extern "C" homekit_characteristic_t cha_switch_on;
extern "C" homekit_characteristic_t cha_brightness;
extern "C" char serial[16];
extern "C" char device_name[32];
