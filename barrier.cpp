#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

using std::vector, std::thread;

sem_t barrier;
sem_t mutex;
int counter = 0;
int numthreads = 100;
vector<thread> threads;

void count(int thread_id) {

    sem_wait(&mutex);
    printf("Thread %d is at the redezvous\n", thread_id);
    counter = counter + 1;
    printf("counter before passing barrier: %d\n", counter);
    sem_post(&mutex);

    if (counter == numthreads) {
        sem_post(&barrier);
    }

    sem_wait(&barrier);
    sem_post(&barrier);

    sem_wait(&mutex);
    counter = counter - 1;
    printf("counter after passing barrier: %d\n", counter);
    printf("Thread %d is leaving barrier\n", thread_id);
    sem_post(&mutex);
}

int main() {
    sem_init(&barrier, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < numthreads; ++i) {
        threads.push_back(thread(count, i));
    }

    for (thread &t : threads) {
        t.join();
    }

    sem_destroy(&barrier);
    sem_destroy(&mutex);

    return 0;
}