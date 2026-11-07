#ifndef TRAFFIC_SIGNAL_H
#define TRAFFIC_SIGNAL_H

#include "vehicle.h"

// Traffic signal colors
typedef enum {
    RED,
    YELLOW,
    GREEN
} SignalColor;

// Structure for a traffic signal
typedef struct {
    Direction direction;
    SignalColor color;
} TrafficSignal;

// Function declarations
void initializeSignals(TrafficSignal signals[]);

void setNorthSouthGreen(TrafficSignal signals[]);
void setNorthSouthYellow(TrafficSignal signals[]);

void setEastWestGreen(TrafficSignal signals[]);
void setEastWestYellow(TrafficSignal signals[]);

void displaySignals(TrafficSignal signals[]);

int isGreen(TrafficSignal signals[], Direction direction);

#endif