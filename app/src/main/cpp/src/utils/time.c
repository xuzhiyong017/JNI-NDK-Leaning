//
// Created by sky on 20-9-10.
//

#include <sys/time.h>

/**
 *
 * @return microseconds
 */
int64_t getSystemTime(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t ts = (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return ts;
}

