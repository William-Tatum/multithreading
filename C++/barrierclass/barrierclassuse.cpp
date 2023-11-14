#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>
#include "barrierclass.h"

using std::vector, std::thread;

int numthreads = 3;
Barrier barrier(numthreads);
vector<thread> threads;

void count(int thread_id) {
    
    for (int i = 0; i < numthreads; ++i) {
        printf("Thread %d is at the redezvous\n", thread_id);

        barrier.Barrier::wait();

        printf("Thread %d is leaving barrier\n", thread_id);
    }
}

int main() {

    for (int i = 0; i < numthreads; ++i) {
        threads.push_back(thread(count, i));
    }

    for (thread &t : threads) {
        t.join();
    }

    return 0;
}