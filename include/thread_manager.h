#ifndef THREAD_MANAGER_H
#define THREAD_MANAGER_H

#include "traffic_queue.h"
#include "traffic_signal.h"

void startTrafficThreads(
    TrafficQueue queues[],
    TrafficSignal signals[]
);

#endif