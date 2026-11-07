#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define MAX_PROCESSES 4
#define MAX_RESOURCES 3

int checkSafeState(
    int available[],
    int maximum[MAX_PROCESSES][MAX_RESOURCES],
    int allocation[MAX_PROCESSES][MAX_RESOURCES]
);

void runBankersAlgorithm(void);

#endif