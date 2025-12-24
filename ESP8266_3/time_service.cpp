#include "time_service.h"
#include <Arduino.h>
static time_t start_time = 0;
/* ===== Khởi tạo NTP ===== */
void time_init() {
  configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");

  // Chờ NTP sync (non-block ngắn)
  while (time(nullptr) < 100000) {
    delay(100);
  }
}

/* ===== Giây trong ngày ===== */
unsigned long time_now_sec() {
  time_t now = time(nullptr);
  struct tm* t = localtime(&now);

  return t->tm_hour * 3600UL +
         t->tm_min  * 60UL +
         t->tm_sec;
}

/* ===== Giờ ===== */
int time_get_hour() {
  time_t now = time(nullptr);
  return localtime(&now)->tm_hour;
}

/* ===== Phút ===== */
int time_get_minute() {
  time_t now = time(nullptr);
  return localtime(&now)->tm_min;
}
