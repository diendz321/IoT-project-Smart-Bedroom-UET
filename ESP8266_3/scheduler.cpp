#include "scheduler.h"
#include "system_state.h"

/* actuator */
#include "actuator_fan.h"
#include "actuator_light.h"
#include "buzzer.h"
#include "oled.h"

/* service */
#include "mqtt_handler.h"

#include <Arduino.h>

static unsigned long lastRun = 0;

void scheduler_init() {
  lastRun = millis();
}

void scheduler_run() {
  unsigned long now = millis();

  /* chạy mỗi 1 giây */
  if (now - lastRun >= 1000) {
    lastRun = now;

    /* ===== LẤY STATE TỪ MQTT ===== */
    float temp = get_temp();
    bool presence = is_presence();
    bool doorOpen = is_door_open();

    fan_auto_control(temp, presence);
    light_auto_control(presence);
    buzzer_check_alarm(presence);

    oled_update(temp);
  }
}
