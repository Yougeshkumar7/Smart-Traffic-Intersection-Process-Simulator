#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include "traffic_queue.h"

// Create processes for four traffic directions
void startTrafficProcesses(TrafficQueue queues[]);

// Process vehicles for one direction
void handleDirection(TrafficQueue *queue, Direction direction);

#endif