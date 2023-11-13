import barrierclass
from threading import *

numthreads = 3
barrier = barrierclass.Barrier(numthreads)
threads = []
counter = 0

def count(thread_id):
    global counter

    for i in range(numthreads):
        print(f"Thread {thread_id} is at the redezvous")
        
        barrier.wait()

        print(f"Thread {thread_id} is leaving barrier")

for i in range(numthreads):
    threads.append(Thread(target=count, args=(i,)))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()

print("All threads have finished.")
