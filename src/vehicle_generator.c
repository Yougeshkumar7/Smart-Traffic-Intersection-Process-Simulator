#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vehicle_generator.h"
#include "statistics.h"

// Generate unique vehicle IDs
static int nextVehicleID = 1001;

// Initialize random number generator
void initializeVehicleGenerator(void) {
    srand((unsigned int)time(NULL));
}

// Generate one random vehicle
Vehicle generateVehicle(void) {

    Vehicle vehicle;

    vehicle.id = nextVehicleID++;

    vehicle.type = rand() % 5;

    vehicle.direction = rand() % 4;

    // Ambulances get higher priority
    if (vehicle.type == AMBULANCE) {
        vehicle.priority = 2;
    } else {
        vehicle.priority = 1;
    }

    vehicle.waiting_time = 0;

    return vehicle;
}

// Generate multiple vehicles
void generateVehicles(TrafficQueue queues[], int total) {

    const char *directions[] = {
        "NORTH", "SOUTH", "EAST", "WEST"
    };

    for (int i = 0; i < total; i++) {

        Vehicle vehicle = generateVehicle();

        // Check whether the selected queue is full
        if (queues[vehicle.direction].count >= MAX_VEHICLES) {
            printf("\nQueue is full. Vehicle %d could not be added.\n",
                   vehicle.id);
            continue;
        }

        // Add vehicle to its direction queue
        enqueue(&queues[vehicle.direction], vehicle);

        // Update statistics only after successful addition
        recordGeneratedVehicle();

        printf("\nVehicle Generated Successfully!");
        printf("\nVehicle ID: %d", vehicle.id);
        printf("\nVehicle Type: %d", vehicle.type);
        printf("\nDirection: %s", directions[vehicle.direction]);
        printf("\nPriority: %d\n", vehicle.priority);
    }
}