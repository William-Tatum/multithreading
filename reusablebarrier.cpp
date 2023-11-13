#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

using std::vector, std::thread;

sem_t barrier;
sem_t barrier2;
sem_t mutex;
int counter = 0;
int numthreads = 3;
vector<thread> threads;

void count(int thread_id) {
    
    for (int i = 0; i < numthreads; ++i) {
    
        sem_wait(&mutex);
        printf("Thread %d is at the redezvous\n", thread_id);
        counter = counter + 1;
        printf("counter before passing barrier: %d\n", counter);
        
        if (counter == numthreads) {
            sem_wait(&barrier2);
            sem_post(&barrier);
        }

        sem_post(&mutex);

        sem_wait(&barrier);
        sem_post(&barrier);

        sem_wait(&mutex);
        counter = counter - 1;
        printf("counter after passing barrier: %d\n", counter);
        printf("Thread %d is leaving barrier\n", thread_id);

        if (counter == 0) {
            sem_wait(&barrier);
            sem_post(&barrier2);
        }
        sem_post(&mutex);

        sem_wait(&barrier2);
        sem_post(&barrier2);
    }
}

int main() {
    sem_init(&barrier, 0, 0);
    sem_init(&barrier2, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < numthreads; ++i) {
        threads.push_back(thread(count, i));
    }

    for (thread &t : threads) {
        t.join();
    }

    sem_destroy(&barrier);
    sem_destroy(&barrier2);
    sem_destroy(&mutex);

    return 0;
}