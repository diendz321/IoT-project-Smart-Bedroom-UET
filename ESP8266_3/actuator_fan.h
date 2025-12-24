// actuator_fan.h
#ifndef ACTUATOR_FAN_H
#define ACTUATOR_FAN_H


void fan_init();
void fan_auto_control(float temp, bool presence);
void fan_force(bool on);
void fan_set_speed(int level);
void set_temp_threshold(float threshold);

#endif