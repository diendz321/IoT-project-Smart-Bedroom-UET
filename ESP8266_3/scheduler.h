#ifndef SCHEDULER_H
#define SCHEDULER_H

/* Khởi tạo scheduler */
void scheduler_init();

/* Hàm chạy trong loop(), non-blocking, mỗi 1 giây */
void scheduler_run();

#endif
