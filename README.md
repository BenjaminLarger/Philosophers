# Philosophers

`Philosophers` is a project in the 42 curriculum that involves solving the classic Dining Philosophers problem. This project helps you understand concurrency, thread management, and synchronization in C.

## Overview

The `Philosophers` project simulates a scenario where philosophers alternately think, eat, and sleep. The challenge is to manage the synchronization of multiple threads to prevent deadlocks and ensure that each philosopher can access shared resources (forks) without conflict.

## Features

- **Thread Management:** Create and manage multiple threads to simulate each philosopher's actions.
- **Synchronization:** Use mutexes or other synchronization primitives to prevent race conditions and ensure safe access to shared resources.
- **Deadlock Prevention:** Implement strategies to avoid deadlocks, ensuring that the simulation runs smoothly.
- **Customizable Parameters:** Allow customization of parameters such as the number of philosophers, time to eat, time to sleep, and time to die.

## Getting Started

To get started with `Philosophers`, clone the repository and compile the program using the provided Makefile:

```bash
git clone https://github.com/BenjaminLarger/philosophers.git
cd philosophers
make

