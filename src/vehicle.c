#include <stdio.h>
#include "vehicle.h"

void displayVehicle(Vehicle vehicle) {

    const char *types[] = {
        "Car", "Bus", "Truck", "Ambulance", "Motorcycle"
    };

    const char *directions[] = {
        "North", "South", "East", "West"
    };

    printf("\n========== VEHICLE INFORMATION ==========\n");
    printf("Vehicle ID: %d\n", vehicle.id);
    printf("Vehicle Type: %s\n", types[vehicle.type]);
    printf("Direction: %s\n", directions[vehicle.direction]);
    printf("Priority: %d\n", vehicle.priority);
    printf("Waiting Time: %d seconds\n", vehicle.waiting_time);
    printf("=========================================\n");
}