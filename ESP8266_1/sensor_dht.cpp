
// sensor_dht.cpp
#include <DHT.h>
#include "sensor_dht.h"


#define DHTPIN D2
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


void dht_init() {
  dht.begin();
}


float dht_read() {
  float t = dht.readTemperature();
  if (isnan(t)) return -1;  // lỗi đọc
  return t;
}