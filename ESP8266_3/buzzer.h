// buzzer.h
#ifndef BUZZER_H
#define BUZZER_H


void buzzer_init();
void buzzer_check_alarm(bool presence);
void buzzer_stop();
void set_alarm_time(int hour, int minute);

#endif