#ifndef VEHICLE_H
#define VEHICLE_H

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

typedef enum {
    CAR,
    BUS,
    TRUCK,
    AMBULANCE,
    MOTORCYCLE
} VehicleType;

typedef struct {
    int id;
    VehicleType type;
    Direction direction;
    int priority;
    int waiting_time;
} Vehicle;

void displayVehicle(Vehicle vehicle);

#endif