
#include <stdio.h>
#include <stdlib.h>
#include <sys/random.h>
#include <errno.h>

#include "vehicle_generator.h"
#include "statistics.h"

static int nextVehicleID = 1001;

// Generate a secure random number within a range
static int getRandomNumber(int limit) {
    unsigned int randomValue;

    while (1) {
        ssize_t result = getrandom(&randomValue, sizeof(randomValue), 0);

        if (result == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("getrandom failed");
            exit(EXIT_FAILURE);
        }

        if (result != sizeof(randomValue)) {
            fprintf(stderr, "Random number generation failed.\n");
            exit(EXIT_FAILURE);
        }

        // Avoid modulo bias
        unsigned int threshold = (unsigned int)(-limit) % limit;

        if (randomValue >= threshold) {
            return (int)(randomValue % limit);
        }
    }
}

// Initialize vehicle generator
void initializeVehicleGenerator(void) {
    nextVehicleID = 1001;
}

// Generate one random vehicle
Vehicle generateVehicle(void) {

    Vehicle vehicle;

    vehicle.id = nextVehicleID++;

    vehicle.type = getRandomNumber(5);

    vehicle.direction = getRandomNumber(4);

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

        if (queues[vehicle.direction].count >= MAX_VEHICLES) {

            printf("\nQueue is full. Vehicle %d could not be added.\n",
                   vehicle.id);

            continue;
        }

        enqueue(&queues[vehicle.direction], vehicle);

        recordGeneratedVehicle();

        printf("\nVehicle Generated Successfully!");

        printf("\nVehicle ID: %d", vehicle.id);

        printf("\nVehicle Type: %d", vehicle.type);

        printf("\nDirection: %s", directions[vehicle.direction]);

        printf("\nPriority: %d\n", vehicle.priority);
    }
}
