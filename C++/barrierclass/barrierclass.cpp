#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>
#include "barrierclass.h"

    Barrier::Barrier(int n) : n(n), count(0) {
        sem_init(&this->mutex, 0, 1);
        sem_init(&this->turnstile, 0, 0);
        sem_init(&this->turnstile2, 0, 0);
    }

    Barrier::~Barrier() {
        sem_destroy(&this->mutex);
        sem_destroy(&this->turnstile);
        sem_destroy(&this->turnstile2);
    }

    void Barrier::phase1() {
        sem_wait(&this->mutex);
        this->count += 1;

        printf("count before: %d\n", this->count);

        if (this->count == this->n) {
            for (int i = 0; i < this->n; ++i) {
                sem_post(&this->turnstile);
            }
        }

        sem_post(&this->mutex);

        sem_wait(&this->turnstile);
    }

    void Barrier::phase2() {
        sem_wait(&this->mutex);
        this->count -= 1;

        printf("count after: %d\n", this->count);

        if (this->count == 0) {
            for (int i = 0; i < this->n; ++i) {
                sem_post(&this->turnstile2);
            }
        }

        sem_post(&this->mutex);

        sem_wait(&this->turnstile2);
    }

    void Barrier::wait() {
        this->phase1();
        this->phase2();
    }