from threading import *

barrier = Semaphore(0)
barrier2 = Semaphore(0)
mutex = Semaphore(1)
threads = []
counter = 0
numthreads = 10

def count(thread_id):
    global counter

    for i in range(numthreads):
        mutex.acquire()

        print(f"Thread {thread_id} is at the redezvous")
        counter = counter + 1
        print(f"counter before passing barrier: {counter}")
        
        if counter == numthreads:
            barrier.release(numthreads)
        
        mutex.release()

        barrier.acquire()

        mutex.acquire()
        
        counter = counter - 1
        print(f"counter after passing barrier: {counter}")
        print(f"Thread {thread_id} is leaving barrier")
        
        if counter == 0:
            barrier2.release(numthreads)
        
        mutex.release()

        barrier2.acquire()

for i in range(numthreads):
    threads.append(Thread(target=count, args=(i,)))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print("All threads have finished.")
