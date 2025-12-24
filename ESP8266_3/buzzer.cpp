// buzzer.cpp
#include "buzzer.h"
#include <Arduino.h>
#include <Ticker.h>
#include "time_service.h"

#define BUZZER_PIN D5


// Thời gian báo thức (giây trong ngày) – sẽ set từ MQTT/Blynk sau
unsigned long alarmTimeSec = 7 * 3600;  // 07:00:00


Ticker buzzerTicker;
bool buzzerActive = false;
bool alarmTriggered = false;


// ISR của Ticker – chạy trong ngắt timer
void buzzer_stop_isr() {
  digitalWrite(BUZZER_PIN, LOW);
  buzzerActive = false;
}


void set_alarm_time(int hour, int minute) {
  alarmTimeSec = hour * 3600 + minute * 60;
  alarmTriggered = false;  // cho phép kêu lại khi đổi giờ
}

void buzzer_init() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Haha");
}


void buzzer_check_alarm(bool presence) {
  if (alarmTriggered || buzzerActive) return;


  // Thời gian hiện tại
  unsigned long nowSec = time_now_sec();
  Serial.print("nowSec = ");
  Serial.print(nowSec);
  Serial.print("  alarmTimeSec = ");
  Serial.println(alarmTimeSec);


  if (presence && nowSec == alarmTimeSec) {
    digitalWrite(BUZZER_PIN, HIGH);  // bật còi
    buzzerActive = true;
    alarmTriggered = true;

    Serial.println("[BUZZER] ON (Alarm Triggered)");
    // Sau 5s sẽ tự tắt còi (KHÔNG BLOCK)
    buzzerTicker.once(5, buzzer_stop_isr);
  }
  Serial.println("Đéo có gì?");
}
