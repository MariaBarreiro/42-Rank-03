# 🎓 42 — Rank 03

Rank 03 of the 42 curriculum: concurrency, shell implementation, and a programming exam.

![Rank](https://img.shields.io/badge/42%20Rank-03-5c6ac4?style=for-the-badge)
![Time](https://img.shields.io/badge/Estimated%20time-280%20hours%20%2B%20exam-007ec6?style=for-the-badge)

---

## 📚 Projects

| Project | Grade | Time | Main topic |
|---|---:|---:|---|
| 🧠 [Philosophers](https://github.com/MariaBarreiro/42_Philo) | **100/100** | ~70 h | Concurrent programming |
| 🐚 [minishell](https://github.com/MariaBarreiro/42_Minishell) | **100/100** | ~210 h | Building a simple shell · Group project |
| ⏱️ Exam Rank 03 | **100/100** | 2 days reported | Programming assessment |

---

## 🧠 Philosophers

> Simulate philosophers sharing forks while eating, sleeping, and thinking.

![Grade](https://img.shields.io/badge/Grade-100%2F100-brightgreen?style=flat-square)
![Time](https://img.shields.io/badge/Time-~70%20hours-blue?style=flat-square)

**What I learned**
- How to create and coordinate threads with `pthread`
- How mutexes protect shared resources
- How to reason about race conditions, deadlocks, and timing

**Compile and run**

```sh
make
./philo 5 800 200 200
```

Arguments are the philosopher count, time to die, time to eat, and time to sleep, in milliseconds. An optional fifth argument sets how many times each philosopher must eat.

---

## 🐚 minishell

> Create a simple shell that parses commands and runs them using Unix processes.

![Grade](https://img.shields.io/badge/Grade-100%2F100-brightgreen?style=flat-square)
![Time](https://img.shields.io/badge/Time-~210%20hours-blue?style=flat-square)
![Team project](https://img.shields.io/badge/Group%20project-Yes-8a63d2?style=flat-square)

**What I learned**
- How to tokenize and parse shell input
- How to execute commands with `fork` and `execve`
- How pipes, redirections, heredocs, environment variables, and signals work
- How to plan and integrate work on a larger project as a team

**Compile and run**

On Linux, install the Readline development library if needed:

```sh
sudo apt-get install libreadline-dev
```

Then build and launch the shell:

```sh
make
./minishell
```

---

## ⏱️ Exam Rank 03

> A two-day programming assessment.

![Grade](https://img.shields.io/badge/Grade-100%2F100-brightgreen?style=flat-square)
![Time](https://img.shields.io/badge/Time-2%20days%20reported-lightgrey?style=flat-square)
