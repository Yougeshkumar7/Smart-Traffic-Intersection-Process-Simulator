#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "process_manager.h"

static const char *directionNames[] = {
    "NORTH",
    "SOUTH",
    "EAST",
    "WEST"
};

// Child process displays information about one direction
void handleDirection(TrafficQueue *queue, Direction direction) {

    printf("\n----------------------------------\n");

    printf("Child Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    printf("Managing %s Traffic\n",
           directionNames[direction]);

    printf("Vehicles waiting in queue: %d\n",
           queue->count);

    // Display vehicles without removing them
    for (int i = 0; i < queue->count; i++) {

        int index = (queue->front + i) % MAX_VEHICLES;

        Vehicle vehicle = queue->vehicles[index];

        printf("Vehicle ID: %d\n", vehicle.id);
    }

    printf("%s Process Completed.\n",
           directionNames[direction]);

    printf("----------------------------------\n");
}

// Create four child processes
void startTrafficProcesses(TrafficQueue queues[]) {

    pid_t pid;

    printf("\n========== PROCESS MANAGEMENT ==========\n");

    printf("Parent Process ID: %d\n", getpid());

    // Create one child for each direction
    for (int i = 0; i < 4; i++) {

        pid = fork();

        if (pid < 0) {

            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        else if (pid == 0) {

            // Child process
            handleDirection(&queues[i], (Direction)i);

            exit(EXIT_SUCCESS);
        }
    }

    // Parent waits for all child processes
    for (int i = 0; i < 4; i++) {

        int status;

        pid_t finished = wait(&status);

        if (finished == -1) {

            perror("wait failed");
        }

        else if (WIFEXITED(status)) {

            printf("\nChild process %d finished with status %d.\n",
                   finished,
                   WEXITSTATUS(status));
        }
    }

    printf("\nAll child processes completed.\n");

    printf("Parent process continues simulation.\n");
}