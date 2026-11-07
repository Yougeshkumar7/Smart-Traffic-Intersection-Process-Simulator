#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "process_manager.h"

// Direction names
const char *directionNames[] = {
    "NORTH",
    "SOUTH",
    "EAST",
    "WEST"
};

// Handle vehicles in one direction
void handleDirection(TrafficQueue *queue, Direction direction) {

    printf("\n----------------------------------\n");

    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    printf("Managing %s Traffic\n",
           directionNames[direction]);

    printf("Vehicles in Queue: %d\n", queue->count);

    // Process each vehicle in this queue
    while (queue->count > 0) {

        Vehicle vehicle = queue->vehicles[queue->front];

        printf("\nVehicle ID: %d", vehicle.id);
        printf("\nDirection: %s",
               directionNames[vehicle.direction]);

        printf("\nVehicle Processed Successfully!\n");

        dequeue(queue);
    }

    printf("\n%s Traffic Process Completed.\n",
           directionNames[direction]);

    printf("----------------------------------\n");
}

// Create four child processes
void startTrafficProcesses(TrafficQueue queues[]) {

    pid_t pid;

    printf("\n========== PROCESS MANAGEMENT ==========\n");

    printf("Parent Process ID: %d\n", getpid());

    for (int i = 0; i < 4; i++) {

        pid = fork();

        if (pid < 0) {

            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        else if (pid == 0) {

            // Child process
            handleDirection(&queues[i], i);

            exit(EXIT_SUCCESS);
        }
    }

    // Parent waits for all four child processes
    for (int i = 0; i < 4; i++) {

        int status;

        if (wait(&status) == -1) {
            perror("wait failed");
        }
        else if (WIFEXITED(status)) {
            printf("\nChild process finished with status: %d\n",
                   WEXITSTATUS(status));
        }
    }

    printf("\nAll traffic processes completed.\n");
}