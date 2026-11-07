#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vehicle_generator.h"

// Generate unique vehicle IDs
static int nextVehicleID = 1001;

// Initialize random number generator
void initializeVehicleGenerator() {

    srand(time(NULL));
}

// Generate one random vehicle
Vehicle generateVehicle() {

    Vehicle vehicle;

    // Assign unique ID
    vehicle.id = nextVehicleID++;

    // Generate random vehicle type
    vehicle.type = rand() % 5;

    // Generate random direction
    vehicle.direction = rand() % 4;

    // Ambulances get higher priority
    if (vehicle.type == AMBULANCE) {
        vehicle.priority = 2;
    }
    else {
        vehicle.priority = 1;
    }

    // Initial waiting time
    vehicle.waiting_time = 0;

    return vehicle;
}

// Generate multiple vehicles
void generateVehicles(TrafficQueue queues[], int total) {

    for (int i = 0; i < total; i++) {

        // Generate a vehicle
        Vehicle vehicle = generateVehicle();

        // Add vehicle to its direction queue
        enqueue(&queues[vehicle.direction], vehicle);

        printf("\nVehicle Generated Successfully!");
        printf("\nVehicle ID: %d", vehicle.id);
        printf("\nDirection: %d", vehicle.direction);
        printf("\nPriority: %d\n", vehicle.priority);
    }
}