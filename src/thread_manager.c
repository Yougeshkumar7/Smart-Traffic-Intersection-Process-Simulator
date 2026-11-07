#include <stdio.h>
#include <pthread.h>

#include "thread_manager.h"
#include "synchronization.h"
#include "statistics.h"

typedef struct {
    TrafficQueue *queue;
    Direction direction;
    TrafficSignal *signals;
} ThreadData;

static const char *directionNames[] = {
    "NORTH", "SOUTH", "EAST", "WEST"
};

// Function executed by each traffic thread
static void *handleTraffic(void *argument) {

    ThreadData *data = (ThreadData *)argument;

    TrafficQueue *queue = data->queue;
    Direction direction = data->direction;

    printf("\nThread %lu managing %s traffic.\n",
           (unsigned long)pthread_self(),
           directionNames[direction]);

    // Check traffic signal
    if (!isGreen(data->signals, direction)) {

        printf("%s signal is RED or YELLOW.\n",
               directionNames[direction]);

        return NULL;
    }

    // Process vehicles in the direction's queue
    while (queue->count > 0) {

        // Check signal before requesting intersection access
        if (!isGreen(data->signals, direction)) {
            break;
        }

        Vehicle vehicle = queue->vehicles[queue->front];

        // Request permission to enter
        if (enterIntersection() != 0) {
            break;
        }

        // Recheck signal after receiving permission
        if (!isGreen(data->signals, direction)) {
            leaveIntersection();
            break;
        }

        printf("\nVehicle ID: %d\n", vehicle.id);
        printf("Vehicle Type: %d\n", vehicle.type);
        printf("Direction: %s\n", directionNames[direction]);

        printf("Vehicle crossed successfully!\n");

        // Remove processed vehicle
        dequeue(queue);

        // Update statistics
        recordProcessedVehicle(vehicle.waiting_time);

        // Allow another vehicle to enter
        leaveIntersection();
    }

    printf("\n%s traffic thread completed.\n",
           directionNames[direction]);

    return NULL;
}

// Create threads for two directions in a phase
static void runTrafficPhase(
    TrafficQueue queues[],
    TrafficSignal signals[],
    Direction first,
    Direction second
) {

    pthread_t threads[2];

    ThreadData data[2];

    Direction directions[2] = {first, second};

    int created[2] = {0, 0};

    for (int i = 0; i < 2; i++) {

        data[i].queue = &queues[directions[i]];
        data[i].direction = directions[i];
        data[i].signals = signals;

        if (pthread_create(
                &threads[i],
                NULL,
                handleTraffic,
                &data[i]
            ) == 0) {

            created[i] = 1;

        } else {

            printf("Could not create %s traffic thread.\n",
                   directionNames[directions[i]]);
        }
    }

    // Wait for both threads
    for (int i = 0; i < 2; i++) {

        if (created[i]) {
            pthread_join(threads[i], NULL);
        }
    }
}

// Start traffic processing
void startTrafficThreads(
    TrafficQueue queues[],
    TrafficSignal signals[]
) {

    printf("\n========== THREAD MANAGEMENT ==========\n");

    // NORTH-SOUTH PHASE
    printf("\n========== NORTH-SOUTH GREEN ==========\n");

    setNorthSouthGreen(signals);
    displaySignals(signals);

    runTrafficPhase(
        queues,
        signals,
        NORTH,
        SOUTH
    );

    // NORTH-SOUTH YELLOW
    printf("\n========== NORTH-SOUTH YELLOW ==========\n");

    setNorthSouthYellow(signals);
    displaySignals(signals);

    // EAST-WEST PHASE
    printf("\n========== EAST-WEST GREEN ==========\n");

    setEastWestGreen(signals);
    displaySignals(signals);

    runTrafficPhase(
        queues,
        signals,
        EAST,
        WEST
    );

    // EAST-WEST YELLOW
    printf("\n========== EAST-WEST YELLOW ==========\n");

    setEastWestYellow(signals);
    displaySignals(signals);

    printf("\nAll traffic threads completed.\n");
}