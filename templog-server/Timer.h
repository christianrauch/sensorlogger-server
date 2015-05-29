#ifndef __TIMER_H__
#define __TIMER_H__

#include <sys/timerfd.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>

class Timer {
    private:
        int fd;

    public:
        void set(const time_t period);
        unsigned long long wait();
};

#endif
