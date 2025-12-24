// actuator_fan.cpp
#include "actuator_fan.h"
#include <Arduino.h>

#define FAN_PIN D3


bool forceOff = false;
int fanSpeed = 0;  // 0-1023
float tempThreshold = 20;


void fan_init() {
  pinMode(FAN_PIN, OUTPUT);
}


void fan_force(bool on) {
  forceOff = !on;
  if (forceOff) analogWrite(FAN_PIN, 0);
}


void fan_set_speed(int level) {
  if (level == 0) fanSpeed = 400;
  if (level == 1) fanSpeed = 600;
  if (level == 2) fanSpeed = 1023;
}


void fan_auto_control(float temp, bool presence) {
  if (forceOff) return;
  if (presence && temp > tempThreshold) {
    analogWrite(FAN_PIN, fanSpeed);
    Serial.println("Diệp");
  }
  else
    analogWrite(FAN_PIN, 0);
}

void set_temp_threshold(float threshold) {
  tempThreshold = threshold;
}