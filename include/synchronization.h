#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

int initializeSynchronization(void);

void enterIntersection(void);
void leaveIntersection(void);

void destroySynchronization(void);

#endif