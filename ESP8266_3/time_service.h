#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include <time.h>

/*
 * Khởi tạo NTP
 * Gọi 1 lần sau khi WiFi connected
 */
void time_init();

/*
 * Lấy thời gian hiện tại (giây trong ngày)
 */
unsigned long time_now_sec();

/*
 * Lấy giờ/phút (phục vụ OLED, debug)
 */
int time_get_hour();
int time_get_minute();

#endif
