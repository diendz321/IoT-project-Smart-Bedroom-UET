#include <Arduino.h>
// actuator_servo.cpp
#include "actuator_servo.h"
#include <Servo.h>
#include <Arduino.h>

// #define SERVO_PIN D5
// #define SERVO_OPEN_ANGLE 90
// #define SERVO_CLOSE_ANGLE 0
// #define DOOR_OPEN_TIME 5000  // 5 giây

// Minh họa bằng led
#define LED_PIN D8
#define DOOR_OPEN_TIME 5000  // 5 giây

// Servo doorServo;
// unsigned long doorOpenMillis = 0;
// bool doorIsOpen = false;

unsigned long doorOpenMillis = 0;
bool doorIsOpen = false;

void servo_init() {
  // doorServo.attach(5);
  // doorServo.write(SERVO_CLOSE_ANGLE);  // cửa đóng ban đầu
  // delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // cửa đóng ban đầu (LED OFF)
}


void servo_open_door() {
  // doorServo.write(SERVO_OPEN_ANGLE);  // mở cửa
  // doorOpenMillis = millis();          // ghi lại thời điểm mở
  // doorIsOpen = true;

  digitalWrite(LED_PIN, HIGH);  // mở cửa (LED ON)
  doorOpenMillis = millis();    // ghi lại thời điểm mở
  doorIsOpen = true;

  Serial.println("[LED] Door OPEN (LED ON)");
}


void servo_task() {
  // // Nếu cửa đang mở và đã quá 5s thì đóng lại
  // if (doorIsOpen && (millis() - doorOpenMillis >= DOOR_OPEN_TIME)) {
  //   doorServo.write(SERVO_CLOSE_ANGLE);
  //   doorIsOpen = false;
  // }

  // Nếu cửa đang mở và đã quá 5s thì đóng lại
  if (doorIsOpen && (millis() - doorOpenMillis >= DOOR_OPEN_TIME)) {
    digitalWrite(LED_PIN, LOW);  // đóng cửa (LED OFF)
    doorIsOpen = false;

    Serial.println("[LED] Door CLOSED (LED OFF)");
  }
}

bool servo_is_door_open() {
  return doorIsOpen;
}