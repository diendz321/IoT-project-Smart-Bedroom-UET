#include "scheduler.h"
#include "sensor_dht.h"
#include "sensor_sonar.h"
#include "mqtt_handler.h"
#include "actuator_servo.h"
#include "sensor_rfid.h"
#include <Arduino.h>

static unsigned long counter = 0;

unsigned long lastSensorRead = 0;

void scheduler_init() {
  lastSensorRead = millis();
}

void scheduler_run() {
  rfid_check();
  unsigned long now = millis();

  // Đọc cảm biến mỗi 1s
  if (now - lastSensorRead >= 1000) {
    lastSensorRead = now;
    servo_task();
    bool doorOpen = servo_is_door_open();
    float temp = dht_read();
    bool presence = sonar_detect();

    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Presence: "); Serial.println(presence);
    Serial.print("Door Open: "); Serial.println(doorOpen);
    
    mqtt_publish_temperature(temp);
    mqtt_publish_presence(presence);
    mqtt_publish_door_status(doorOpen);
    Serial.print("Counter: ");
    Serial.println(counter++);   // 0 → 1 → 2 → ...
  }
}