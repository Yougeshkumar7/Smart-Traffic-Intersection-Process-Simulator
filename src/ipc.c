#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ipc.h"

void demonstrateIPC(void) {

    int pipefd[2];
    pid_t pid;
    char message[] = "Traffic update: North-South signal is GREEN.";
    char receivedMessage[100];

    printf("\n========== IPC: PIPE COMMUNICATION ==========\n");

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return;
    }

    // Create a child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(pipefd[0]);
        close(pipefd[1]);
        return;
    }

    // Child process
    if (pid == 0) {

        close(pipefd[1]);  // Close unused write end

        int bytesRead = read(pipefd[0], receivedMessage,
                             sizeof(receivedMessage) - 1);

        if (bytesRead < 0) {
            perror("Pipe read failed");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }

        receivedMessage[bytesRead] = '\0';

        printf("\nChild Process ID: %d\n", getpid());
        printf("Message received from parent:\n");
        printf("%s\n", receivedMessage);

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }

    // Parent process
    else {

        close(pipefd[0]);  // Close unused read end

        printf("\nParent Process ID: %d\n", getpid());
        printf("Sending traffic information to child...\n");

        if (write(pipefd[1], message, sizeof(message)) == -1) {
            perror("Pipe write failed");
        }

        close(pipefd[1]);

        wait(NULL);

        printf("\nParent received confirmation: Child process completed.\n");
    }

    printf("\n========== IPC COMPLETED ==========\n");
}