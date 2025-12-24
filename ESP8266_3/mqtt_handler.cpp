#include "mqtt_handler.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "config.h"

#include "system_state.h"

/* actuator */
#include "actuator_fan.h"
#include "actuator_light.h"
#include "buzzer.h"

WiFiClient espClient;
PubSubClient client(espClient);


void mqtt_callback(char* topic, byte* payload, unsigned int length) {

  /* ===== COPY PAYLOAD RA BUFFER TĨNH ===== */
  static char msg[32];  // đủ cho command
  if (length >= sizeof(msg)) length = sizeof(msg) - 1;

  memcpy(msg, payload, length);
  msg[length] = '\0';

  /* ===== SO SÁNH TOPIC KHÔNG DÙNG String ===== */
  if (strcmp(topic, TOPIC_CMD_FAN_FORCE) == 0) {
    fan_force(msg[0] == '1');
  } else if (strcmp(topic, TOPIC_TEMP) == 0) {
    set_temp(atof(msg));
  }

  else if (strcmp(topic, TOPIC_DOOR) == 0) {
    set_door_status(strcmp(msg, "OPEN") == 0);
  }

  else if (strcmp(topic, TOPIC_PRESENCE) == 0) {
    set_presence(msg[0] == '1');
  }

  else if (strcmp(topic, TOPIC_CMD_FAN_SPEED) == 0) {
    fan_set_speed(atoi(msg));
  }

  else if (strcmp(topic, TOPIC_CMD_LIGHT_FORCE) == 0) {
    light_force(msg[0] == '1');
  }

  else if (strcmp(topic, TOPIC_CMD_TEMP_THRESH) == 0) {
    set_temp_threshold(atof(msg));
  }

  /* ---------- GIỜ BÁO THỨC ---------- */
  else if (strcmp(topic, TOPIC_CMD_ALARM) == 0) {
    // format: HH:MM
    int hh = (msg[0] - '0') * 10 + (msg[1] - '0');
    int mm = (msg[3] - '0') * 10 + (msg[4] - '0');
    set_alarm_time(hh, mm);

    /* ===== DEBUG IN RA THỜI GIAN ===== */
    Serial.print("[ALARM] Set time = ");
    if (hh < 10) Serial.print("0");
    Serial.print(hh);
    Serial.print(":");
    if (mm < 10) Serial.print("0");
    Serial.println(mm);

    Serial.print("[ALARM] alarmTimeSec = ");
    Serial.println((unsigned long)(hh * 3600 + mm * 60));
  }
}

/* ================= MQTT INIT ================= */
void mqtt_init() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqtt_callback);
}
/* ================= MQTT LOOP (NON-BLOCKING) ================= */
void mqtt_loop() {
  static unsigned long lastAttempt = 0;

  if (!client.connected()) {
    if (millis() - lastAttempt >= 1000) {
      lastAttempt = millis();

      if (client.connect("ESP8266_3")) {
        Serial.println("[MQTT] Connected");
        /* ===== SUBSCRIBE TOPIC ===== */
        client.subscribe(TOPIC_CMD_FAN_FORCE);
        client.subscribe(TOPIC_CMD_FAN_SPEED);
        client.subscribe(TOPIC_CMD_LIGHT_FORCE);
        client.subscribe(TOPIC_CMD_TEMP_THRESH);
        client.subscribe(TOPIC_CMD_ALARM);

        client.subscribe(TOPIC_TEMP);
        client.subscribe(TOPIC_DOOR);
        client.subscribe(TOPIC_PRESENCE);
      } else {
        Serial.print("[MQTT] Failed, rc=");
        Serial.println(client.state());
      }
    }
  }

  client.loop();  // bắt buộc, non-blocking
}
