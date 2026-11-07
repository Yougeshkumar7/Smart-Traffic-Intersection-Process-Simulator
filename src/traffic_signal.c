#include <stdio.h>
#include "traffic_signal.h"

// Initialize all signals to RED
void initializeSignals(TrafficSignal signals[]) {

    for (int i = 0; i < 4; i++) {
        signals[i].direction = i;
        signals[i].color = RED;
    }
}

// North and South GREEN, East and West RED
void setNorthSouthGreen(TrafficSignal signals[]) {

    signals[NORTH].color = GREEN;
    signals[SOUTH].color = GREEN;

    signals[EAST].color = RED;
    signals[WEST].color = RED;
}

// North and South YELLOW
void setNorthSouthYellow(TrafficSignal signals[]) {

    signals[NORTH].color = YELLOW;
    signals[SOUTH].color = YELLOW;

    signals[EAST].color = RED;
    signals[WEST].color = RED;
}

// East and West GREEN, North and South RED
void setEastWestGreen(TrafficSignal signals[]) {

    signals[EAST].color = GREEN;
    signals[WEST].color = GREEN;

    signals[NORTH].color = RED;
    signals[SOUTH].color = RED;
}

// East and West YELLOW
void setEastWestYellow(TrafficSignal signals[]) {

    signals[EAST].color = YELLOW;
    signals[WEST].color = YELLOW;

    signals[NORTH].color = RED;
    signals[SOUTH].color = RED;
}

// Display all traffic signals
void displaySignals(TrafficSignal signals[]) {

    char *colors[] = {"RED", "YELLOW", "GREEN"};

    char *directions[] = {
        "NORTH",
        "SOUTH",
        "EAST",
        "WEST"
    };

    printf("\n========== TRAFFIC SIGNAL STATUS ==========\n");

    for (int i = 0; i < 4; i++) {

        printf("%s : %s\n",
               directions[i],
               colors[signals[i].color]);
    }

    printf("===========================================\n");
}

// Check whether a direction has GREEN signal
int isGreen(TrafficSignal signals[], Direction direction) {

    if (signals[direction].color == GREEN) {
        return 1;
    }

    return 0;
}