#include <stdio.h>
#include <semaphore.h>
#include <thread>

sem_t aArrived;
sem_t bArrived;

void A() {
    printf("Drone A: Picked up the package.\n");
    sem_post(&bArrived);
    sem_wait(&aArrived);
    printf("Drone A: Package handed off to Drone B.\n");
}

void B() {
    sem_wait(&bArrived);
    printf("Drone B: Arrived at the redezvous point.\n");
    sem_post(&aArrived);
    printf("Drone B: Received package and is delivering to the final destination.\n");
}

int main() {
    sem_init(&aArrived, 0, 0);
    sem_init(&bArrived, 0, 0);

    std::thread t1(A);
    std::thread t2(B);
    
    t1.join();
    t2.join();

    sem_destroy(&aArrived);
    sem_destroy(&bArrived);

    return 0;
}