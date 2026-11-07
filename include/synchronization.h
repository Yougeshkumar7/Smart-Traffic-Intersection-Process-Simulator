#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

int initializeSynchronization(void);

int enterIntersection(void);
void leaveIntersection(void);

void destroySynchronization(void);

#endif