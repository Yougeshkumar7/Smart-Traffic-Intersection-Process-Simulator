
#include <stdio.h>

#include "vehicle.h"
#include "traffic_queue.h"
#include "traffic_signal.h"
#include "vehicle_generator.h"
#include "process_manager.h"
#include "ipc.h"
#include "thread_manager.h"
#include "synchronization.h"
#include "resource_manager.h"
#include "statistics.h"

int main(void) {

    // Create four traffic queues
    TrafficQueue queues[4];

    // Create four traffic signals
    TrafficSignal signals[4];

    printf("\n============================================\n");
    printf("   SMART TRAFFIC INTERSECTION SIMULATOR\n");
    printf("============================================\n");

    // STEP 1: Initialize queues
    printf("\n========== QUEUE INITIALIZATION ==========\n");

    for (int i = 0; i < 4; i++) {
        initializeQueue(&queues[i]);
    }

    printf("All traffic queues initialized.\n");

    // STEP 2: Initialize traffic signals
    printf("\n========== SIGNAL INITIALIZATION ==========\n");

    initializeSignals(signals);
    displaySignals(signals);

    // STEP 3: Initialize vehicle generator
    initializeVehicleGenerator();

    // STEP 4: Initialize statistics
    initializeStatistics();

    // STEP 5: Initialize synchronization
    printf("\n========== SYNCHRONIZATION ==========\n");

    if (initializeSynchronization() != 0) {
        printf("Synchronization initialization failed.\n");
        return 1;
    }

    // STEP 6: Generate vehicles
    printf("\n========== VEHICLE GENERATION ==========\n");

    generateVehicles(queues, 12);

    // STEP 7: Display all queues
    printf("\n========== NORTH QUEUE ==========\n");
    displayQueue(queues[NORTH]);

    printf("\n========== SOUTH QUEUE ==========\n");
    displayQueue(queues[SOUTH]);

    printf("\n========== EAST QUEUE ==========\n");
    displayQueue(queues[EAST]);

    printf("\n========== WEST QUEUE ==========\n");
    displayQueue(queues[WEST]);

    // STEP 8: Demonstrate process management
    printf("\n========== PROCESS MANAGEMENT ==========\n");

    startTrafficProcesses(queues);

    // STEP 9: Demonstrate IPC using pipes
    printf("\n========== INTER-PROCESS COMMUNICATION ==========\n");

    demonstrateIPC();

    // STEP 10: Run Banker's Algorithm
    printf("\n========== RESOURCE MANAGEMENT ==========\n");

    runBankersAlgorithm();

    // STEP 11: NORTH-SOUTH traffic phase
    printf("\n========== NORTH-SOUTH TRAFFIC PHASE ==========\n");

    setNorthSouthGreen(signals);
    displaySignals(signals);

    startTrafficThreads(queues);

    setNorthSouthYellow(signals);
    displaySignals(signals);

    // STEP 12: EAST-WEST traffic phase
    printf("\n========== EAST-WEST TRAFFIC PHASE ==========\n");

    setEastWestGreen(signals);
    displaySignals(signals);

    startTrafficThreads(queues);

    setEastWestYellow(signals);
    displaySignals(signals);

    // STEP 13: Display final statistics
    printf("\n========== FINAL STATISTICS ==========\n");

    displayStatistics();

    // STEP 14: Destroy synchronization resources
    destroySynchronization();

    printf("\n============================================\n");
    printf("       SIMULATION COMPLETED\n");
    printf("============================================\n");

    return 0;
}
