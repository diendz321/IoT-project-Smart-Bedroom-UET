#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

void mqtt_init();
void mqtt_loop();

/* publish trạng thái */
void mqtt_publish_temperature(float t);
void mqtt_publish_presence(bool p);
void mqtt_publish_door_status(bool open);
#endif
