from threading import *

leaderQueue = Semaphore(0)
followerQueue = Semaphore(0)
mutex = Semaphore(1)
count = 0
threads = []
numthreads = 10

def leader():
    followerQueue.release()
    leaderQueue.acquire()

    mutex.acquire()
    global count
    count += 1
    print(f"count: {count}\n")
    mutex.release()

def follower():
    leaderQueue.release()
    followerQueue.acquire()

    mutex.acquire()
    global count

    count -= 1
    print(f"count: {count}\n")
    mutex.release()

for i in range(numthreads):
    threads.append(Thread(target=leader))

for i in range(numthreads):
    threads.append(Thread(target=follower))

for thread in threads:
    thread.start()
    
for thread in threads:
    thread.join()

print("All threads have finished.")
