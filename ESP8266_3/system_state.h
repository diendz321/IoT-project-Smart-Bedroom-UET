#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

/* ===== SETTERS ===== */
void set_temp(float t);
void set_door_status(bool open);
void set_presence(bool present);

/* ===== GETTERS ===== */
float get_temp();
bool is_door_open();
bool is_presence();
#endif
