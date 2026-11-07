#include <stdio.h>
#include "resource_manager.h"

int checkSafeState(
    int available[],
    int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int allocation[MAX_PROCESSES][MAX_RESOURCES]
) {

    int need[MAX_PROCESSES][MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];

    int work[MAX_RESOURCES];

    // Calculate remaining resource needs
    for (int i = 0; i < MAX_PROCESSES; i++) {

        for (int j = 0; j < MAX_RESOURCES; j++) {

            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Copy available resources
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int completed = 0;

    // Find a safe execution sequence
    while (completed < MAX_PROCESSES) {

        int found = 0;

        for (int i = 0; i < MAX_PROCESSES; i++) {

            if (finish[i] == 0) {

                int possible = 1;

                for (int j = 0; j < MAX_RESOURCES; j++) {

                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[completed] = i;

                    finish[i] = 1;
                    completed++;
                    found = 1;
                }
            }
        }

        if (!found) {

            printf("\nSystem is in an UNSAFE state!\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\n");

    printf("Safe Sequence: ");

    for (int i = 0; i < MAX_PROCESSES; i++) {

        printf("P%d", safeSequence[i]);

        if (i < MAX_PROCESSES - 1) {
            printf(" -> ");
        }
    }

    printf("\n");

    return 1;
}

void runBankersAlgorithm(void) {

    // Available resources
    int available[MAX_RESOURCES] = {3, 3, 2};

    // Maximum resource requirements
    int maximum[MAX_PROCESSES][MAX_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2}
    };

    // Currently allocated resources
    int allocation[MAX_PROCESSES][MAX_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1}
    };

    printf("\n========== BANKER'S ALGORITHM ==========\n");

    printf("\nChecking available resources...\n");

    checkSafeState(available, maximum, allocation);

    printf("\n========================================\n");
}