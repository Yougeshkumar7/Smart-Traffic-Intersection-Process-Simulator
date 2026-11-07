#ifndef VEHICLE_GENERATOR_H
#define VEHICLE_GENERATOR_H

#include "traffic_queue.h"

// Initialize random vehicle generation
void initializeVehicleGenerator();

// Generate one random vehicle
Vehicle generateVehicle();

// Generate multiple vehicles
void generateVehicles(TrafficQueue queues[], int total);

#endif