# This is showing what happens if it is not explicitly
# ordered in order to prevent this

from threading import *

aArrived = Semaphore(0)
bArrived = Semaphore(0)

def A():
    print("Drone A: Picked up the package.")
    aArrived.release() # A drone pickup complete
    bArrived.acquire() # A drone waits for B drone
    print("Drone A: Package handed off to Drone B.")

def B():
    print("Drone B: Arrived at the redezvous point.")
    bArrived.release() # B drone has arrived
    aArrived.acquire() # waiting for A drone to arrive
    print("Drone B: Received package and is delivering to the final destination.")

t1 = Thread(None, A)
t2 = Thread(None, B)

t1.start()
t2.start()

t1.join()
t2.join()
