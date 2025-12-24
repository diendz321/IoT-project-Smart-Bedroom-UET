#include "HardwareSerial.h"
#include "actuator_light.h"
#include <Arduino.h>

/* Chân LED */
#define LED_ROOM_PIN   D7   // đèn phòng

/* Trạng thái ép từ Blynk */
static bool lightEnable = true;

void light_init() {
  pinMode(LED_ROOM_PIN, OUTPUT);

  digitalWrite(LED_ROOM_PIN, LOW);
  Serial.println("[LIGHT] Init: OFF");
}

/*
 * Logic tự động
 */
void light_auto_control(bool presence) {
  if (!lightEnable) {
    digitalWrite(LED_ROOM_PIN, LOW);
    return;
  }

  /* Đèn phòng */
  if (presence) {
    digitalWrite(LED_ROOM_PIN, HIGH);
    Serial.println("[LIGHT]: ON");
  } else {
    digitalWrite(LED_ROOM_PIN, LOW);
  }
}

/*
 * Ép bật / tắt từ Blynk
 */
void light_force(bool enable) {
  lightEnable = enable;

  if (!enable) {
    digitalWrite(LED_ROOM_PIN, LOW);
  }
}
