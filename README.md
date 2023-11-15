# Multithreading
**My experience following the little book of semaphores.**

## Languages
* C++
* Python

## Rendezvous
>This is a file showing the rendezvous problem.

If A arrives first, it waits for B. When B arrives, it wakes A and might proceed immediately to its wait in which case it blocks, allowing A to reach its
signal, after which both threads can proceed.

## Mutex
>This is a file showing the mutual exclusion problem using exclusively semaphores.

## Multiplex
>This is a file showing the multiplex problem.

## Barrier
>This is a file showing the barrier problem.

## Reusable Barrier
>This is a file showing the reusable barrier problem.

## Preloaded Turnstile
>This is a different approach to the reusable barrier problem.

## Barrier Class
>This is a file which shows how you would create a barrier class.

## Barrier Class User
>This shows how to use the barrier class.

## Queue
>This is a file showing the queue problem.

## Exclusive Queue
>This is a file showing the exclusive queue problem.
