#ifndef CONFIG_H
#define CONFIG_H

/*********** WIFI ***********/
#define WIFI_SSID       "DienDz"
#define WIFI_PASSWORD   "0362719204"

/*********** MQTT ***********/
#define MQTT_SERVER     "192.168.1.3"   // máy tính cá nhân
#define MQTT_PORT       1883

/*********** MQTT TOPICS ***********/
// ESP8266_1 → ESP8266_2
#define TOPIC_TEMP          "room/temperature"
#define TOPIC_DOOR          "room/door"
#define TOPIC_PRESENCE      "room/presence"

// ESP8266_2 → ESP8266_1
#define TOPIC_CMD_FAN_FORCE     "cmd/fan_force"
#define TOPIC_CMD_FAN_SPEED     "cmd/fan_speed"
#define TOPIC_CMD_LIGHT_FORCE   "cmd/light_force"
#define TOPIC_CMD_TEMP_THRESH   "cmd/temp_threshold"
#define TOPIC_CMD_ALARM         "cmd/alarm"

/*********** BLYNK ***********/
#define BLYNK_TEMPLATE_ID "TMPL6G24lTVKb"
#define BLYNK_TEMPLATE_NAME "IoT Project"
#define BLYNK_AUTH_TOKEN "gjcvXDPdG6uyYC0fTffludAw3DlbzD0v"

/*********** BLYNK VIRTUAL PINS ***********/
#define VPIN_TEMP_DISPLAY     V0
#define VPIN_DOOR_STATUS      V1
#define VPIN_PRESENCE_DISPLAY V7

#define VPIN_FAN_FORCE        V2
#define VPIN_FAN_SPEED        V3
#define VPIN_LIGHT_FORCE      V4
#define VPIN_TEMP_THRESHOLD  V5
#define VPIN_ALARM_TIME       V6

#endif
