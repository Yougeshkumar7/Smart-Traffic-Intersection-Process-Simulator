#ifndef STATISTICS_H
#define STATISTICS_H

void initializeStatistics(void);

void recordGeneratedVehicle(void);

void recordProcessedVehicle(int waitingTime);

void displayStatistics(void);

#endif