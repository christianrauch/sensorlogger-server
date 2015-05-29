#include "Timer.h"

void Timer::set(const time_t period) {
    // create file descriptor
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(fd<0) {
        std::cerr<<strerror(errno)<<std::endl;
    }

    // set timer values
    const timespec time = {.tv_sec = period, .tv_nsec = 0};
    const itimerspec timer = {.it_interval = time, .it_value = time};

    // activate timer
    if(timerfd_settime(fd, 0, &timer, NULL) < 0) {
        std::cout<<strerror(errno)<<std::endl;
    }
}

unsigned long long Timer::wait() {
    unsigned long long missed;
    read(fd, &missed, sizeof(missed));
    return missed;
}

