#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"
#include <BlynkSimpleEsp32.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

/* ===== PRIVATE ===== */
static PubSubClient* mqtt;

/* =====  MQTT INIT ===== */
void mqtt_init(PubSubClient* client) {
  mqtt = client;
  mqtt->setCallback(mqtt_callback);
}

/* ===== MQTT STATE ===== */
float mqtt_temp = 0.0;
String mqtt_door = "";
bool mqtt_presence = false;

/* =====================================================
 *                BLYNK UI UPDATE
 * ===================================================== */
void blynk_update_temperature(float temp) {
  Blynk.virtualWrite(VPIN_TEMP_DISPLAY, temp);
}

void blynk_update_door(String state) {
  Blynk.virtualWrite(VPIN_DOOR_STATUS, state);
}

void blynk_update_presence(String state) {
  if (state == "1") {
    Blynk.virtualWrite(VPIN_PRESENCE_DISPLAY, "PRESENCE");
  } else {
    Blynk.virtualWrite(VPIN_PRESENCE_DISPLAY, "NO PRESENCE");
  }
}

/* =====================================================
 *                BLYNK CALLBACK
 * ===================================================== */

/* ===== BUTTON ÉP TẮT QUẠT ===== */
BLYNK_WRITE(VPIN_FAN_FORCE) {
  int value = param.asInt();
  Serial.print("[BLYNK] FAN_FORCE = ");
  Serial.println(value);
  mqttClient.publish(
    TOPIC_CMD_FAN_FORCE,
    value ? "1" : "0"
  );
}

/* ===== TỐC ĐỘ QUẠT ===== */
BLYNK_WRITE(VPIN_FAN_SPEED) {
  int speed = param.asInt();  // 0–2
  mqttClient.publish(
    TOPIC_CMD_FAN_SPEED,
    String(speed).c_str()
  );
}

/* ===== ÉP TẮT ĐÈN ===== */
BLYNK_WRITE(VPIN_LIGHT_FORCE) {
  int value = param.asInt();
  mqttClient.publish(
    TOPIC_CMD_LIGHT_FORCE,
    value ? "1" : "0"
  );
}

/* ===== NGƯỠNG NHIỆT ===== */
BLYNK_WRITE(VPIN_TEMP_THRESHOLD) {
  float threshold = param.asFloat();
  mqttClient.publish(
    TOPIC_CMD_TEMP_THRESH,
    String(threshold).c_str()
  );
}

/* ===== GIỜ BÁO THỨC ===== */
BLYNK_WRITE(VPIN_ALARM_TIME) {
  String timeStr = param.asString();  // "HH:MM"

  if (timeStr.length() != 5 || timeStr.charAt(2) != ':')
    return;

  mqttClient.publish(
    TOPIC_CMD_ALARM,
    timeStr.c_str()
  );
}

/* ===== MQTT CALLBACK ===== */
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (uint16_t i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  /* ---- NHIỆT ĐỘ ---- */
  if (strcmp(topic, TOPIC_TEMP) == 0) {
    mqtt_temp = msg.toFloat();
    blynk_update_temperature(mqtt_temp);
  }

  /* ---- CỬA ---- */
  else if (strcmp(topic, TOPIC_DOOR) == 0) {
    mqtt_door = msg;
    blynk_update_door(mqtt_door);
  }

  /* ---- HIỆN DIỆN ---- */
  else if (strcmp(topic, TOPIC_PRESENCE) == 0) {
    mqtt_presence = (msg == "1");
    blynk_update_presence(msg);
  }
}

/* ===== MQTT RECONNECT ===== */
void mqtt_reconnect() {
  static unsigned long lastAttempt = 0;

  if (millis() - lastAttempt < 1000) return;
  lastAttempt = millis();

  if (mqttClient.connect("ESP8266_2")) {
    Serial.println("[MQTT] Connected");
    mqttClient.subscribe(TOPIC_TEMP);
    mqttClient.subscribe(TOPIC_DOOR);
    mqttClient.subscribe(TOPIC_PRESENCE);
  }
  else {
    Serial.print("[MQTT] Failed, rc=");
    Serial.println(mqttClient.state());
  }
}

void setup() {
  Serial.begin(115200);

  /******** WIFI ********/
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  /******** MQTT ********/
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqtt_init(&mqttClient);

  /******** BLYNK ********/
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();
}


void loop() {
  if (!mqttClient.connected()) {
    mqtt_reconnect();
  }
  mqttClient.loop();

  Blynk.run();
}
