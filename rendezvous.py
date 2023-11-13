# The order matters for the drones where the
# redezvous condition needs to go in a certain order
# instead of both of them going when possible

from threading import *

aArrived = Semaphore(0)
bArrived = Semaphore(0)

def A():
    print("Drone A: Picked up the package.")
    bArrived.release() # A drone picked up package and is ready
    aArrived.acquire() # A drone waiting for B drone
    print("Drone A: Package handed off to Drone B.")

def B():
    bArrived.acquire() # B drone arrives and is waiting for A drone
    print("Drone B: Arrived at the redezvous point.")
    aArrived.release() # A drone handed off package and B drone goes off
    print("Drone B: Received package and is delivering to the final destination.")

t1 = Thread(None, A)
t2 = Thread(None, B)

t1.start()
t2.start()

t1.join()
t2.join()
