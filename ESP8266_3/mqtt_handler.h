#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>

/* ===== MQTT API ===== */
void mqtt_init();
void mqtt_loop();

/* ===== MQTT CALLBACK ===== */
void mqtt_callback(char* topic, byte* payload, unsigned int length);

#endif
