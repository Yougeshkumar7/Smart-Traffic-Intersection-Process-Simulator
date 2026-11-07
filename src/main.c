#include <stdio.h>
#include "vehicle.h"
#include "traffic_queue.h"

int main() {

    // Create four direction queues
    TrafficQueue northQueue, southQueue, eastQueue, westQueue;

    // Initialize all queues
    initializeQueue(&northQueue);
    initializeQueue(&southQueue);
    initializeQueue(&eastQueue);
    initializeQueue(&westQueue);

    // Create vehicles
    Vehicle v1 = {101, CAR, NORTH, 1, 5};
    Vehicle v2 = {102, BUS, NORTH, 1, 10};
    Vehicle v3 = {103, AMBULANCE, NORTH, 2, 2};

    Vehicle v4 = {104, CAR, SOUTH, 1, 4};
    Vehicle v5 = {105, TRUCK, EAST, 1, 8};
    Vehicle v6 = {106, MOTORCYCLE, WEST, 1, 3};

    printf("\n========================================\n");
    printf("  SMART TRAFFIC INTERSECTION SIMULATOR\n");
    printf("========================================\n");

    // Add vehicles to their respective queues
    enqueue(&northQueue, v1);
    enqueue(&northQueue, v2);
    enqueue(&northQueue, v3);

    enqueue(&southQueue, v4);
    enqueue(&eastQueue, v5);
    enqueue(&westQueue, v6);

    // Display all direction queues
    printf("\n========== NORTH QUEUE ==========\n");
    displayQueue(northQueue);

    printf("\n========== SOUTH QUEUE ==========\n");
    displayQueue(southQueue);

    printf("\n========== EAST QUEUE ==========\n");
    displayQueue(eastQueue);

    printf("\n========== WEST QUEUE ==========\n");
    displayQueue(westQueue);

    // Simulate green signal for North
    printf("\n--- NORTH TRAFFIC SIGNAL: GREEN ---\n");

    dequeue(&northQueue);

    printf("\nNorth Queue After Vehicle Crossing:\n");
    displayQueue(northQueue);

    printf("\n========================================\n");
    printf("       SIMULATION COMPLETED\n");
    printf("========================================\n");

    return 0;
}