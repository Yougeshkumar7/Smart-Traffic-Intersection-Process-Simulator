#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#include "synchronization.h"

// Mutex protects shared intersection information
static pthread_mutex_t intersectionMutex;

// Semaphore controls access to the intersection
static sem_t intersectionSemaphore;

// Initialize mutex and semaphore
int initializeSynchronization(void) {

    if (pthread_mutex_init(&intersectionMutex, NULL) != 0) {
        printf("Error initializing mutex.\n");
        return -1;
    }

    if (sem_init(&intersectionSemaphore, 0, 1) != 0) {
        printf("Error initializing semaphore.\n");
        pthread_mutex_destroy(&intersectionMutex);
        return -1;
    }

    printf("\nSynchronization initialized successfully.\n");

    return 0;
}

// A vehicle requests permission to enter
void enterIntersection(void) {

    sem_wait(&intersectionSemaphore);

    pthread_mutex_lock(&intersectionMutex);

    printf("\nVehicle has entered the intersection.\n");

    pthread_mutex_unlock(&intersectionMutex);
}

// A vehicle leaves the intersection
void leaveIntersection(void) {

    pthread_mutex_lock(&intersectionMutex);

    printf("Vehicle has left the intersection.\n");

    pthread_mutex_unlock(&intersectionMutex);

    sem_post(&intersectionSemaphore);
}

// Destroy synchronization resources
void destroySynchronization(void) {

    sem_destroy(&intersectionSemaphore);

    pthread_mutex_destroy(&intersectionMutex);

    printf("\nSynchronization resources destroyed.\n");
}