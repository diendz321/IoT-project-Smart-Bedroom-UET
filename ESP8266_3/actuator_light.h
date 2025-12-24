#ifndef ACTUATOR_LIGHT_H
#define ACTUATOR_LIGHT_H

/*
 * Khởi tạo GPIO cho đèn
 */
void light_init();

/*
 * Điều khiển đèn tự động
 * presence      : có người trong phòng hay không
 */
void light_auto_control(bool presence);

/*
 * Ép bật/tắt từ MQTT/Blynk
 * enable = true  → cho phép hoạt động tự động
 * enable = false → ép tắt toàn bộ đèn
 */
void light_force(bool enable);

#endif
