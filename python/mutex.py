from threading import *

mutex = Semaphore(1)
counter = 0
threads = []

def count():
    global counter
    
    mutex.acquire()
    counter = counter + 1
    print(counter)
    mutex.release()

for i in range(20):
    threads.append(Thread(target=count))

for thread in threads:
    thread.start()

for thread in threads:
    thread.join()
