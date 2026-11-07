#include <stdio.h>
#include <pthread.h>

#include "thread_manager.h"

typedef struct {
    TrafficQueue *queue;
    Direction direction;
} ThreadData;

const char *threadDirectionNames[] = {
    "NORTH", "SOUTH", "EAST", "WEST"
};

// Function executed by each thread
void *handleTraffic(void *arg) {

    ThreadData *data = (ThreadData *)arg;

    TrafficQueue *queue = data->queue;
    Direction direction = data->direction;

    printf("\n----------------------------------\n");
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    printf("Managing %s Traffic\n", threadDirectionNames[direction]);
    printf("Vehicles in Queue: %d\n", queue->count);

    while (queue->count > 0) {

        Vehicle vehicle = queue->vehicles[queue->front];

        printf("\nVehicle ID: %d", vehicle.id);
        printf("\nVehicle Type: %d", vehicle.type);
        printf("\nVehicle crossed successfully!\n");

        dequeue(queue);
    }

    printf("\n%s Traffic Thread Completed.\n",
           threadDirectionNames[direction]);

    printf("----------------------------------\n");

    return NULL;
}

// Create and manage four traffic threads
void startTrafficThreads(TrafficQueue queues[]) {

    pthread_t threads[4];
    ThreadData threadData[4];

    printf("\n========== THREAD MANAGEMENT ==========\n");

    // Create four threads
    for (int i = 0; i < 4; i++) {

        threadData[i].queue = &queues[i];
        threadData[i].direction = i;

        if (pthread_create(&threads[i], NULL,
                           handleTraffic, &threadData[i]) != 0) {

            printf("Error creating thread for %s traffic.\n",
                   threadDirectionNames[i]);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < 4; i++) {

        pthread_join(threads[i], NULL);
    }

    printf("\nAll traffic threads completed successfully.\n");
}