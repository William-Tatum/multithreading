#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

using std::vector, std::thread;

sem_t leaderQueue;
sem_t followerQueue;
sem_t mutex;
int counter = 0;
int numthreads = 10;
vector<thread> threads;

void leader() {
    sem_post(&followerQueue);
    sem_wait(&leaderQueue);

    sem_wait(&mutex);
    counter++;
    printf("count: %d\n", counter);
    sem_post(&mutex);
}

void follower() {
    sem_post(&leaderQueue);
    sem_wait(&followerQueue);

    sem_wait(&mutex);
    counter--;
    printf("count: %d\n", counter);
    sem_post(&mutex);
}

int main() {
    sem_init(&leaderQueue, 0, 0);
    sem_init(&followerQueue, 0, 0);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < numthreads; ++i) {
        threads.push_back(thread(leader));
    }

    for (int i = 0; i < numthreads; ++i) {
        threads.push_back(thread(follower));
    }

    for (thread &t : threads) {
        t.join();
    }

    sem_destroy(&leaderQueue);
    sem_destroy(&followerQueue);
    sem_destroy(&mutex);

    return 0;
}