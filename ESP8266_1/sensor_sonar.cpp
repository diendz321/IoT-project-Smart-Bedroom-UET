// sensor_sonar.cpp  (đã thay bằng cảm biến hồng ngoại)
#include "sensor_sonar.h"
#include <Arduino.h>

#define IR_PIN D1   // Chân OUT của cảm biến hồng ngoại

void sonar_init() {
  // pinMode(IR_PIN, INPUT);
  
  // Minh họa bằng button
  pinMode(IR_PIN, INPUT_PULLUP);
}

bool sonar_detect() {
  // int irState = digitalRead(IR_PIN);

  // // Với module IR LM393:
  // // LOW  = phát hiện vật
  // // HIGH = không có vật
  // if (irState == LOW) {
  //   Serial.println("[IR] Object detected");
  //   return true;
  // } else {
  //   Serial.println("[IR] No object");
  //   return false;
  // }
  
  // Minh họa bằng button
  bool currentState = digitalRead(IR_PIN);

  // Phát hiện cạnh nhấn (HIGH → LOW)
  if (currentState == LOW) {
    Serial.println("[BUTTON] Press detected");
    return true;
  }
  return false;
}

