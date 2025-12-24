// oled.cpp
#include "time_service.h"  
#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


Adafruit_SSD1306 display(128, 64, &Wire, -1);


void oled_init() {
  Serial.println("Diệp");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Lỗi");
    for(;;);
  }
  display.clearDisplay();
  display.display();
  Serial.println("Diện");
}


void oled_update(float temp) {
  int hour   = time_get_hour();
  int minute = time_get_minute();
  time_t now = time(nullptr);
  int second = localtime(&now)->tm_sec;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  /* ----- Hiển thị nhiệt độ ----- */
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temp, 1);
  display.print(" C");

  /* ----- Hiển thị thời gian ----- */
  display.setCursor(0, 16);
  display.print("Time: ");

  if (hour < 10)   display.print("0");
  display.print(hour);
  display.print(":");

  if (minute < 10) display.print("0");
  display.print(minute);
  display.print(":");

  if (second < 10) display.print("0");
  display.print(second);

  display.display();

  /* ===== DEBUG SERIAL ===== */
  Serial.print("[TIME] ");
  if (hour < 10)   Serial.print("0");
  Serial.print(hour);
  Serial.print(":");

  if (minute < 10) Serial.print("0");
  Serial.print(minute);
  Serial.print(":");

  if (second < 10) Serial.print("0");
  Serial.println(second);
}