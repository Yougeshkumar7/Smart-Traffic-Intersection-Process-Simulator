#include <stdio.h>
#include "statistics.h"

// Statistics variables
static int totalGenerated = 0;
static int totalProcessed = 0;
static int totalWaitingTime = 0;

// Initialize statistics
void initializeStatistics(void) {

    totalGenerated = 0;
    totalProcessed = 0;
    totalWaitingTime = 0;

    printf("\nTraffic statistics initialized.\n");
}

// Record a newly generated vehicle
void recordGeneratedVehicle(void) {

    totalGenerated++;
}

// Record a processed vehicle
void recordProcessedVehicle(int waitingTime) {

    totalProcessed++;

    if (waitingTime >= 0) {
        totalWaitingTime += waitingTime;
    }
}

// Display simulation statistics
void displayStatistics(void) {

    int totalWaiting = totalGenerated - totalProcessed;

    if (totalWaiting < 0) {
        totalWaiting = 0;
    }

    double averageWaitingTime = 0.0;

    if (totalProcessed > 0) {

        averageWaitingTime =
            (double)totalWaitingTime / totalProcessed;
    }

    printf("\n========================================\n");
    printf("       TRAFFIC SIMULATION STATISTICS\n");
    printf("========================================\n");

    printf("Total Vehicles Generated : %d\n", totalGenerated);

    printf("Total Vehicles Processed : %d\n", totalProcessed);

    printf("Total Vehicles Waiting   : %d\n", totalWaiting);

    printf("Total Waiting Time       : %d\n", totalWaitingTime);

    printf("Average Waiting Time     : %.2f\n", averageWaitingTime);

    printf("========================================\n");
}