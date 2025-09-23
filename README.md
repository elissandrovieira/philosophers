# Philosophers - 42 Project

**Philosophers** is a project from the 42 curriculum designed to simulate the classic Dining Philosophers problem. The goal is to implement a multithreaded program that handles concurrency, synchronization, and process management in C.

This project helped me strengthen my understanding of **threads, mutexes, semaphores, and parallelism**, as well as improve my problem-solving skills in real-world concurrency scenarios.

## Key Learnings

- **Multithreading:** Learned how to create and manage multiple threads efficiently.
- **Synchronization:** Used mutexes and semaphores to prevent race conditions and deadlocks.
- **Timing & Sleep Management:** Managed precise timing for philosophers’ actions (eating, thinking, sleeping).
- **Resource Sharing:** Implemented strategies to safely share forks (resources) among threads.
- **Problem Solving:** Applied logical thinking to detect and avoid deadlocks in concurrent systems.
- **C Programming Mastery:** Improved understanding of pointers, structs, and memory management in a multithreaded context.

## Features

- Simulates multiple philosophers sitting at a table with forks.
- Ensures that no philosopher starves while others are eating.
- Supports configurable number of philosophers and timing parameters.
- Handles concurrent execution safely and efficiently.

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/elissandrovieira/philosophers.git
cd philosophers
```

2. Compile the program:

```bash
make
```
  
3. Run with desired parameters:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200 7
```

Thank you for checking out my **Philosophers** project. This experience greatly improved my understanding of concurrency and multithreading in C!
