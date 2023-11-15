from threading import *

leaderQueue = Semaphore(0)
followerQueue = Semaphore(0)
mutex = Semaphore(1)
rendezvous = Semaphore(0)
leaders = followers = 0
threads = []
count = 0
numthreads = 10

def leader():
    mutex.acquire()
    global count, followers, leaders

    if followers > 0:
        followers -= 1
        followerQueue.release()
    else:
        leaders += 1
        mutex.release()
        leaderQueue.acquire()

    count += 1
    print(f"count: {count}\n")
    rendezvous.acquire()
    mutex.release()
    

def follower():
    mutex.acquire()
    global count, followers, leaders

    if leaders > 0:
        leaders -= 1
        leaderQueue.release()
    else:
        followers += 1
        mutex.release()
        followerQueue.acquire()
    
    count -= 1
    print(f"count: {count}\n")
    rendezvous.release()

for i in range(numthreads):
    threads.append(Thread(target=leader))

for i in range(numthreads):
    threads.append(Thread(target=follower))

for thread in threads:
    thread.start()
    
for thread in threads:
    thread.join()

print("All threads have finished.")
