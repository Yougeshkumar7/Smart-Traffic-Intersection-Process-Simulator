#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "traffic_queue.h"

void startTrafficProcesses(TrafficQueue queues[]);

void handleDirection(TrafficQueue *queue, Direction direction);

#endif