from threading import *
from time import *
from random import *

multiplex = Semaphore(3)
countsem = Semaphore(1)
threads = []
counter = 0

def count(thread_id):
    global counter
    
    multiplex.acquire()
    print(f"Thread {thread_id} is accessing the resource")

    countsem.acquire()
    counter = counter + 1
    print(f"counter: {counter}")
    countsem.release()

    sleep(uniform(0.1, 1.0))
    print(f"Thread {thread_id} is leaving the resource")
    multiplex.release()

for i in range(20):
    threads.append(Thread(target=count, args=(i,)))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print("All threads have finished.")
