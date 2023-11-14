from threading import *

barrier = Semaphore(0)
mutex = Semaphore(1)
threads = []
counter = 0
numthreads = 100

def count(thread_id):
    global counter

    mutex.acquire()
    print(f"Thread {thread_id} is at the redezvous")
    counter = counter + 1
    print(f"counter before passing barrier: {counter}")
    mutex.release()

    if counter == numthreads:
        barrier.release()

    barrier.acquire()
    barrier.release()

    mutex.acquire()
    counter = counter - 1
    print(f"counter after passing barrier: {counter}")
    print(f"Thread {thread_id} is leaving barrier")
    mutex.release()

for i in range(numthreads):
    threads.append(Thread(target=count, args=(i,)))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print("All threads have finished.")
