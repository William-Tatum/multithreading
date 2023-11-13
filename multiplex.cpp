#include <stdio.h>
#include <semaphore.h>
#include <thread>
#include <vector>
#include <chrono>
#include <random>

using std::vector, std::thread, std::this_thread::sleep_for, std::chrono::milliseconds,
std::random_device, std::default_random_engine, std::uniform_real_distribution;

random_device rd;
default_random_engine eng(rd());
uniform_real_distribution<float> distr(0.1, 1.0);

sem_t multiplex;
sem_t countsem;
int counter = 0;
float duration = distr(eng);
vector<thread> threads;

void count(int thread_id) {
    sem_wait(&multiplex);
    printf("Thread %d is accessing the resource\n", thread_id);

    sem_wait(&countsem);
    counter = counter + 1;
    printf("counter: %d\n", counter);
    sem_post(&countsem);

    sleep_for(milliseconds(static_cast<int>(duration * 1000)));
    printf("Thread %d is leaving the resource\n", thread_id);
    sem_post(&multiplex);
}

int main() {
    sem_init(&multiplex, 0, 3);
    sem_init(&countsem, 0, 1);

    for (size_t i = 0; i < 20; ++i) {
        threads.push_back(thread(count, i));
    }

    for (auto &t : threads) {
        t.join();
    }

    sem_destroy(&multiplex);
    sem_destroy(&countsem);

    return 0;
}
