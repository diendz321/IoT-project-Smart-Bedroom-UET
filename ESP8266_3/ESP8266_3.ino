#include <ESP8266WiFi.h>
#include "config.h"
#include "actuator_fan.h"
#include "actuator_light.h"
#include "buzzer.h"
#include "mqtt_handler.h"
#include "oled.h"
#include "scheduler.h"
#include "time_service.h"
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  mqtt_init();
  time_init();
  fan_init();
  light_init();
  buzzer_init();
  oled_init();
  scheduler_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  mqtt_loop();
  scheduler_run();
}
