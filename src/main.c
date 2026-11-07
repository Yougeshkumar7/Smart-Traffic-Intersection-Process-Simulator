
#include <stdio.h>

#include "vehicle.h"
#include "traffic_queue.h"
#include "traffic_signal.h"
#include "vehicle_generator.h"
#include "process_manager.h"

int main() {

    // Create four direction queues
    TrafficQueue queues[4];

    // Create traffic signals
    TrafficSignal signals[4];

    printf("\n========================================\n");
    printf(" SMART TRAFFIC INTERSECTION SIMULATOR\n");
    printf("========================================\n");

    // STEP 1: Initialize all four queues
    for (int i = 0; i < 4; i++) {
        initializeQueue(&queues[i]);
    }

    // STEP 2: Initialize traffic signals
    initializeSignals(signals);

    printf("\nAll traffic queues initialized.\n");

    // STEP 3: Initialize vehicle generator
    initializeVehicleGenerator();

    // STEP 4: Generate 12 random vehicles
    printf("\n========== VEHICLE GENERATION ==========\n");

    generateVehicles(queues, 12);

    // STEP 5: Display all four queues
    printf("\n========== NORTH QUEUE ==========\n");
    displayQueue(queues[NORTH]);

    printf("\n========== SOUTH QUEUE ==========\n");
    displayQueue(queues[SOUTH]);

    printf("\n========== EAST QUEUE ==========\n");
    displayQueue(queues[EAST]);

    printf("\n========== WEST QUEUE ==========\n");
    displayQueue(queues[WEST]);

    // STEP 6: NORTH-SOUTH TRAFFIC PHASE
    printf("\n\n========== NORTH-SOUTH PHASE ==========\n");

    setNorthSouthGreen(signals);
    displaySignals(signals);

    // STEP 7: EAST-WEST TRAFFIC PHASE
    printf("\n\n========== EAST-WEST PHASE ==========\n");

    setEastWestGreen(signals);
    displaySignals(signals);

    // STEP 8: Start four child processes
    printf("\n========== PROCESS MANAGEMENT ==========\n");

    startTrafficProcesses(queues);

    // STEP 9: Final signal status
    printf("\n========== FINAL SIGNAL STATUS ==========\n");

    setEastWestYellow(signals);
    displaySignals(signals);

    printf("\n========================================\n");
    printf("       SIMULATION COMPLETED\n");
    printf("========================================\n");

    return 0;
}
