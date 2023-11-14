#ifndef BARRIER_H
#define BARRIER_H

#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

class Barrier {
    int n;
    int count;
    sem_t mutex;
    sem_t turnstile;
    sem_t turnstile2;

public:
    Barrier(int n);
    ~Barrier();
    void phase1();
    void phase2();
    void wait();
};

#endif