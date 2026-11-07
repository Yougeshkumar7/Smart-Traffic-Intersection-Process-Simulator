#include <stdio.h>

#include "vehicle.h"
#include "traffic_queue.h"
#include "traffic_signal.h"

int main() {

    // Create four direction queues
    TrafficQueue northQueue, southQueue, eastQueue, westQueue;

    // Create traffic signals
    TrafficSignal signals[4];

    // Initialize queues
    initializeQueue(&northQueue);
    initializeQueue(&southQueue);
    initializeQueue(&eastQueue);
    initializeQueue(&westQueue);

    // Initialize traffic signals
    initializeSignals(signals);

    // Create vehicles
    Vehicle v1 = {101, CAR, NORTH, 1, 5};
    Vehicle v2 = {102, BUS, NORTH, 1, 10};
    Vehicle v3 = {103, AMBULANCE, NORTH, 2, 2};

    Vehicle v4 = {104, CAR, SOUTH, 1, 4};
    Vehicle v5 = {105, TRUCK, EAST, 1, 8};
    Vehicle v6 = {106, MOTORCYCLE, WEST, 1, 3};

    printf("\n========================================\n");
    printf(" SMART TRAFFIC INTERSECTION SIMULATOR\n");
    printf("========================================\n");

    // Add vehicles to queues
    enqueue(&northQueue, v1);
    enqueue(&northQueue, v2);
    enqueue(&northQueue, v3);

    enqueue(&southQueue, v4);
    enqueue(&eastQueue, v5);
    enqueue(&westQueue, v6);

    // Display queues
    printf("\n========== NORTH QUEUE ==========\n");
    displayQueue(northQueue);

    printf("\n========== SOUTH QUEUE ==========\n");
    displayQueue(southQueue);

    printf("\n========== EAST QUEUE ==========\n");
    displayQueue(eastQueue);

    printf("\n========== WEST QUEUE ==========\n");
    displayQueue(westQueue);

    // PHASE 1: North and South GREEN
    printf("\n\n--- NORTH-SOUTH TRAFFIC PHASE ---\n");

    setNorthSouthGreen(signals);
    displaySignals(signals);

    // North vehicles can cross
    if (isGreen(signals, NORTH)) {

        printf("\nNorth signal is GREEN. Vehicle can cross.\n");
        dequeue(&northQueue);
    }

    // South vehicles can cross
    if (isGreen(signals, SOUTH)) {

        printf("\nSouth signal is GREEN. Vehicle can cross.\n");
        dequeue(&southQueue);
    }

    // PHASE 2: North and South YELLOW
    printf("\n--- NORTH-SOUTH SIGNALS CHANGING ---\n");

    setNorthSouthYellow(signals);
    displaySignals(signals);

    // PHASE 3: East and West GREEN
    printf("\n\n--- EAST-WEST TRAFFIC PHASE ---\n");

    setEastWestGreen(signals);
    displaySignals(signals);

    // East vehicles can cross
    if (isGreen(signals, EAST)) {

        printf("\nEast signal is GREEN. Vehicle can cross.\n");
        dequeue(&eastQueue);
    }

    // West vehicles can cross
    if (isGreen(signals, WEST)) {

        printf("\nWest signal is GREEN. Vehicle can cross.\n");
        dequeue(&westQueue);
    }

    // PHASE 4: East and West YELLOW
    printf("\n--- EAST-WEST SIGNALS CHANGING ---\n");

    setEastWestYellow(signals);
    displaySignals(signals);

    printf("\n========================================\n");
    printf("       SIMULATION COMPLETED\n");
    printf("========================================\n");

    return 0;
}