// actuator_servo.h
#ifndef ACTUATOR_SERVO_H
#define ACTUATOR_SERVO_H


void servo_init();
void servo_open_door();
void servo_task(); // hàm xử lý đóng cửa sau 5s (non-blocking)
bool servo_is_door_open();

#endif