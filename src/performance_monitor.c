//
// Created by Henok Jackson on 08/10/26.
//
#include "../include/performance_monitor.h"

long double measure_exec_time(const perf_metric* perf_metrics_ptr) {
    if (perf_metrics_ptr == nullptr) {
        return 0.0;
    }
	return (long double)(perf_metrics_ptr -> stop_time - perf_metrics_ptr -> start_time)/(CLOCKS_PER_SEC);
}

bool start_perf_test(perf_metric* perf_metrics_ptr) {
    if (perf_metrics_ptr == nullptr) {
        return false;
    }
    perf_metrics_ptr -> start_time = clock();
    return true;
}

bool stop_perf_test(perf_metric* perf_metrics_ptr) {
    if (perf_metrics_ptr == nullptr) {
        return false;
    }
    perf_metrics_ptr -> stop_time = clock();
    return true;
}
