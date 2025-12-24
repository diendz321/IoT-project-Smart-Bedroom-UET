#include <ESP8266WiFi.h>
#include "config.h"
#include "mqtt_handler.h"
#include "sensor_dht.h"
#include "sensor_sonar.h"
#include "sensor_rfid.h"
#include "actuator_servo.h"
#include "scheduler.h"


void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  mqtt_init();          // MQTT client

  
  dht_init();           // Cảm biến nhiệt độ
  sonar_init();         // Cảm biến phát hiện người
  rfid_init();          // RFID

  servo_init();         // Servo cửa

  scheduler_init();     // Bộ lập lịch (millis)
  Serial.println("=== BOOT ===");

}

void loop() {
  mqtt_loop();          // Duy trì MQTT
  scheduler_run();      // Chạy các task định kỳ
}