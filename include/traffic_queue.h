#ifndef TRAFFIC_QUEUE_H
#define TRAFFIC_QUEUE_H

#include "vehicle.h"

#define MAX_VEHICLES 50

typedef struct {
    Vehicle vehicles[MAX_VEHICLES];
    int front;
    int rear;
    int count;
} TrafficQueue;

void initializeQueue(TrafficQueue *queue);
void enqueue(TrafficQueue *queue, Vehicle vehicle);
void displayQueue(TrafficQueue queue);
void dequeue(TrafficQueue *queue);

#endif