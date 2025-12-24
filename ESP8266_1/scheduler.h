#ifndef SCHEDULER_H
#define SCHEDULER_H

/*
 * scheduler_init()
 * ----------------
 * Hàm khởi tạo bộ lập lịch
 * - Gọi 1 lần trong setup()
 * - Khởi tạo các biến thời gian
 */
void scheduler_init();

/*
 * scheduler_run()
 * ---------------
 * Hàm chạy bộ lập lịch
 * - Gọi liên tục trong loop()
 * - Thực hiện các task định kỳ bằng millis()
 * - KHÔNG dùng delay()
 */
void scheduler_run();

#endif
