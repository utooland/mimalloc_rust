#ifndef _TIME_H
#define _TIME_H

#include <stddef.h>

typedef long time_t;
typedef long clock_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

#define CLOCK_MONOTONIC 1
#define CLOCK_REALTIME 0

static inline clock_t clock(void) {
    return 0;
}

static inline int clock_gettime(int clk_id, struct timespec *tp) {
    tp->tv_sec = 0;
    tp->tv_nsec = 0;
    return 0;
}

#endif
