//
// Created by Henok Jackson on 08/10/26.
//
#ifndef FIBCALC_PERFORMANCE_MONITOR_H
#define FIBCALC_PERFORMANCE_MONITOR_H

#include <time.h>

typedef struct {
    clock_t start_time;
    clock_t stop_time;
} perf_metric;

bool start_perf_test(perf_metric*);

bool stop_perf_test(perf_metric*);

long double measure_exec_time(const perf_metric*);

#endif //FIBCALC_PERFORMANCE_MONITOR_H
