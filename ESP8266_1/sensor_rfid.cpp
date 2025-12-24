#include "stdio.h"
// sensor_rfid.cpp
#include "sensor_rfid.h"
#include <SPI.h>
#include <MFRC522.h>
#include "actuator_servo.h"
#include "mqtt_handler.h"


#define SS_PIN D4
#define RST_PIN D3

// #define RFID_BUTTON_PIN D6   // GPIO12 – giả lập RFID bằng button

MFRC522 rfid(SS_PIN, RST_PIN);
byte validUID[4] = { 0xC6, 0xD5, 0x47, 0x01 };


void rfid_init() {
  SPI.begin();
  rfid.PCD_Init();
  // // ===== BUTTON GIẢ LẬP RFID =====
  // pinMode(RFID_BUTTON_PIN, INPUT_PULLUP);

  // Serial.println("[RFID] Button mode enabled (RFID simulated)");
  Serial.println("[RFID] RC522 initialized");
}


void rfid_check() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("[RFID] UID: ");
  bool valid = true;

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");

    if (rfid.uid.uidByte[i] != validUID[i]) {
      valid = false;
    }
  }
  Serial.println();


  if (valid) {
    Serial.println("[RFID] ACCESS GRANTED");
    servo_open_door();
    mqtt_publish_door_status(true);
  } else {
    Serial.println("[RFID] ACCESS DENIED");
    mqtt_publish_door_status(false);
  }


  rfid.PICC_HaltA();
  // // ===== BUTTON GIẢ LẬP RFID =====
  // static bool lastState1 = HIGH;
  // bool currentState1 = digitalRead(RFID_BUTTON_PIN);

  // // Phát hiện nhấn nút (HIGH → LOW)
  // if (lastState1 == HIGH && currentState1 == LOW) {
  //   Serial.println("[RFID] BUTTON PRESSED → ACCESS GRANTED");

  //   servo_open_door();
  //   mqtt_publish_door_status(true);   // nếu hệ của bạn có MQTT

  // }
  // lastState1 = currentState1;
}