#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>

#include "synchronization.h"

static pthread_mutex_t intersectionMutex;
static sem_t intersectionSemaphore;
static int synchronizationReady = 0;

int initializeSynchronization(void) {

    if (pthread_mutex_init(&intersectionMutex, NULL) != 0) {
        fprintf(stderr, "Error initializing mutex.\n");
        return -1;
    }

    if (sem_init(&intersectionSemaphore, 0, 1) != 0) {
        perror("Error initializing semaphore");
        pthread_mutex_destroy(&intersectionMutex);
        return -1;
    }

    synchronizationReady = 1;

    printf("\nMutex and semaphore initialized successfully.\n");

    return 0;
}

// Request permission to enter the intersection
int enterIntersection(void) {

    if (!synchronizationReady) {
        fprintf(stderr, "Synchronization is not initialized.\n");
        return -1;
    }

    // Wait until the intersection becomes available
    while (sem_wait(&intersectionSemaphore) == -1) {

        if (errno != EINTR) {
            perror("sem_wait failed");
            return -1;
        }
    }

    // Lock shared intersection information
    if (pthread_mutex_lock(&intersectionMutex) != 0) {
        sem_post(&intersectionSemaphore);
        fprintf(stderr, "Mutex lock failed.\n");
        return -1;
    }

    printf("\nIntersection access granted to a vehicle.\n");

    return 0;
}

// Release the intersection
void leaveIntersection(void) {

    if (!synchronizationReady) {
        return;
    }

    printf("Vehicle leaving the intersection.\n");

    pthread_mutex_unlock(&intersectionMutex);

    sem_post(&intersectionSemaphore);
}

// Release synchronization resources
void destroySynchronization(void) {

    if (!synchronizationReady) {
        return;
    }

    sem_destroy(&intersectionSemaphore);
    pthread_mutex_destroy(&intersectionMutex);

    synchronizationReady = 0;

    printf("\nSynchronization resources destroyed.\n");
}