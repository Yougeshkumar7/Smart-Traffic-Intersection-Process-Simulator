#include <stdio.h>
#include "traffic_queue.h"

// Initialize an empty queue
void initializeQueue(TrafficQueue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

// Add a vehicle to the queue
void enqueue(TrafficQueue *queue, Vehicle vehicle) {

    if (queue->count == MAX_VEHICLES) {
        printf("Queue is full!\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_VEHICLES;

    queue->vehicles[queue->rear] = vehicle;

    queue->count++;

    printf("Vehicle %d added to queue.\n", vehicle.id);
}

// Display all vehicles
void displayQueue(TrafficQueue queue) {

    if (queue.count == 0) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nVehicles in Queue:\n");

    for (int i = 0; i < queue.count; i++) {

        int index = (queue.front + i) % MAX_VEHICLES;

        printf("Vehicle ID: %d\n",
               queue.vehicles[index].id);
    }
}

void dequeue(TrafficQueue *queue) {

    if (queue->count == 0) {
        printf("Queue is empty!\n");
        return;
    }

    Vehicle vehicle = queue->vehicles[queue->front];

    printf("Vehicle %d crossed the intersection.\n", vehicle.id);

    queue->front = (queue->front + 1) % MAX_VEHICLES;

    queue->count--;
}