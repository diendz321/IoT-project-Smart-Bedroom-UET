#include "system_state.h"

/* ===== BIẾN TRẠNG THÁI TOÀN HỆ THỐNG ===== */
static float currentTemp = 0.0;
static bool doorOpen = false;
static bool presenceDetected = false;

/* ===== SET ===== */
void set_temp(float t) {
  currentTemp = t;
}

void set_door_status(bool open) {
  doorOpen = open;
}

void set_presence(bool present) {
  presenceDetected = present;
}

/* ===== GET ===== */
float get_temp() {
  return currentTemp;
}

bool is_door_open() {
  return doorOpen;
}

bool is_presence() {
  return presenceDetected;
}

