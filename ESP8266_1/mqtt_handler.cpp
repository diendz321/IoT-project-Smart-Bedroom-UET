#include "mqtt_handler.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "config.h"

WiFiClient espClient;
PubSubClient client(espClient);

/* ================= MQTT INIT ================= */
void mqtt_init() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void mqtt_loop() {
  static unsigned long lastAttempt = 0;

  if (!client.connected()) {
    if (millis() - lastAttempt >= 1000) {
      lastAttempt = millis();

      if (client.connect("ESP8266_1")) {
        Serial.println("[MQTT] Connected");
      } else {
        Serial.print("[MQTT] Failed, rc=");
        Serial.println(client.state());
      }
    }
  }

  client.loop();
}

/* ================= MQTT PUBLISH ================= */
void mqtt_publish_temperature(float t) {
  client.publish(TOPIC_TEMP, String(t).c_str());
}

void mqtt_publish_presence(bool p) {
  client.publish(TOPIC_PRESENCE, p ? "1" : "0");
}

void mqtt_publish_door_status(bool open) {
  client.publish(TOPIC_DOOR, open ? "OPEN" : "CLOSE");
}

