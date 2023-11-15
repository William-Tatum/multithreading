#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

using std::vector, std::thread;

sem_t leaderQueue;
sem_t followerQueue;
sem_t mutex;
sem_t rendezvous;
int counter = 0;
int leaders = 0;
int followers = 0;
int numthreads = 10;
vector<thread> threads;

void leader() {
    sem_wait(&mutex);

    if (followers > 0) {
        followers--;
        sem_post(&followerQueue);
    }
    else {
        leaders++;
        sem_post(&mutex);
        sem_wait(&leaderQueue);
    }

    counter++;
    printf("count: %d\n", counter);
    sem_wait(&rendezvous);
    sem_post(&mutex);
}

void follower() {
    sem_wait(&mutex);

    if (leaders > 0) {
        leaders--;
        sem_post(&leaderQueue);
    }
    else {
        followers++;
        sem_post(&mutex);
        sem_wait(&followerQueue);
    }

    counter--;
    printf("count: %d\n", counter);
    sem_post(&rendezvous);
}

int main() {
    sem_init(&leaderQueue, 0, 0);
    sem_init(&followerQueue, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&rendezvous, 0, 0);

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
    sem_destroy(&rendezvous);

    return 0;
}