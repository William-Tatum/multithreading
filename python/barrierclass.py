from threading import *

class Barrier:
    def __init__(self, n):
        self.n = n
        self.count = 0
        self.mutex = Semaphore(1)
        self.turnstile = Semaphore(0)
        self.turnstile2 = Semaphore(0)

    def phase1(self):
        self.mutex.acquire()
        self.count += 1

        print(f"count before: {self.count}")

        if self.count == self.n:
            self.turnstile.release(self.n)
        
        self.mutex.release()

        self.turnstile.acquire()

    def phase2(self):
        self.mutex.acquire()
        self.count -= 1

        print(f"count after: {self.count}")

        if self.count == 0:
            self.turnstile2.release(self.n)

        self.mutex.release()

        self.turnstile2.acquire()

    def wait(self):
        self.phase1()
        self.phase2()
        