# multithreading
My experience following the little book of semaphores.

# sync
This is a file written in both Python and C++ showing the rendezvous problem.

If A arrives first, it waits for B. When B arrives, it wakes A and might
proceed immediately to its wait in which case it blocks, allowing A to reach its
signal, after which both threads can proceed.
