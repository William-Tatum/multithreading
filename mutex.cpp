#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>

using std::vector, std::thread;

sem_t mutex;
int counter = 0;
vector<thread> threads;

void count() {
    sem_wait(&mutex);
    counter = counter + 1;
    printf("counter: %d\n", counter);
    sem_post(&mutex);
}

int main() {
    sem_init(&mutex, 0, 1);

    for (size_t i = 0; i < 20; ++i) {
        threads.push_back(thread(count));
    }

    for (auto &t : threads) {
        t.join();
    }

    sem_destroy(&mutex);

    return 0;
}
