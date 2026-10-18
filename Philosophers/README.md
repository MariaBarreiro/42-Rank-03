*This project has been created as part of the 42 curriculum by mda-enca.*

# Philosophers (philo)

## Description

The **Philosophers** project is an introduction to concurrent programming and synchronization in C. It is based on the classic *Dining Philosophers Problem*, a well-known computer science exercise used to explore issues such as race conditions, deadlocks, and resource sharing.

The goal of this project is to simulate a group of philosophers sitting around a table who alternate between eating, thinking, and sleeping. Each philosopher requires two forks to eat, but forks are shared resources, creating potential conflicts that must be carefully managed.

To solve this, the project implements:
- **Threads** to represent each philosopher
- **Mutexes** to protect shared resources (forks)
- Precise **timing and state management** to track actions such as eating, sleeping, and dying

The challenge lies in ensuring that:
- No philosopher starves
- No data races occur
- The simulation behaves consistently under concurrent execution

This project reinforces key concepts in multithreading, synchronization, and low-level system programming, while also requiring careful design to avoid common concurrency pitfalls.

## Instructions

### 1) Compilation
From the repository root:

```bash
make
```

This builds the executable:
- `./philo`

Useful Makefile targets:

```bash
make        # build
make clean  # remove object files
make fclean # remove object files + binary
make re     # full rebuild
```

### 2) Execution
Program usage:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Parameters are expected in **milliseconds** (except the philosopher count).

Example without meal limit (simulation ends on death):

```bash
./philo 5 800 200 200
```

Example with meal limit (simulation ends when everyone reaches the target meals):

```bash
./philo 5 800 200 200 7
```

## Technical Notes
- Language: C
- Concurrency: `pthread` threads + mutexes
- Time management: `gettimeofday`-based timestamps
- Output is serialized with a dedicated mutex to avoid mixed log lines.

## Project Structure
- `inc/philo.h` — shared declarations, structs, constants, and prototypes.
- `src/` — source files for parsing, initialization, simulation loop, monitoring, output, and cleanup.

## Resources
Classic references related to this project topic:

1. The Dining Philosophers Problem (original synchronization problem):
   - Edsger W. Dijkstra, *Hierarchical ordering of sequential processes*.
2. POSIX Threads programming reference:
   - `man pthread_create`, `man pthread_mutex_lock`, `man pthread_join`.
3. 42 project subject and peer evaluations for `philo` (intra resources).

### AI Usage Disclosure
AI tools were used only as auxiliary support. Their use included:
- structure and draft this `README.md`
- understanding edge cases of the project
- reviewing code structure

AI was **not** used to implement or alter the project source code logic as part of this documentation update.

