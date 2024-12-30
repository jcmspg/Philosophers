# Philosophers
Philosophers exercise for the 42 School curriculum

![image](assets/philosophers.jpeg)

## Introduction
The dining philosophers problem is a classic synchronization problem that is used to illustrate the challenges of avoiding deadlock and coordinating access to shared resources. The problem is stated as follows:

Five silent philosophers sit at a round table with bowls of spaghetti. A fork is placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After they finish eating, they need to put down both forks so they become available to others. A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

The problem is how to design a discipline of behavior (a concurrent algorithm) such that each philosopher will not starve; i.e., they can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

Originated by Edsger Dijkstra as an exercise to illustrate the challenges of avoiding deadlock _a system state in which no progress is possible_ . In the case of the dining philosophers, a deadlock occurs if each philosopher picks up the fork on their right and waits indefinitely for the fork on their left, preventing any of them from eating.

Later, Tony Hoare introduced the problem to the computer science community. The problem was designed to illustrate the challenges of deadlock and the importance of proper synchronization. The problem has since been used in a variety of computer science courses and textbooks.

In a generalized version of the problem, there may be more philosophers than forks, and the forks may be shared from a central location rather than placed between adjacent philosophers.

## Table of Contents
- [Description](#description)
- [Usage](#usage)
- [Example](#example)
- [Options](#options)
- [Rules](#rules)
- [Requirements](#requirements)
- [Notes](#notes)
- [Bonus Part](#bonus-part)
- [Resources](#resources)
- [License](#license)




## Description
This project is an exercise for the 42 School curriculum. The goal is to solve the dining philosophers problem using threads and mutexes.

## Usage
```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Example
```bash
./philo 5 800 200 200
```

## Options
- number_of_philosophers: number of philosophers and forks
- time_to_die: time in milliseconds before a philosopher dies
- time_to_eat: time in milliseconds for a philosopher to eat
- time_to_sleep: time in milliseconds for a philosopher to sleep
- number_of_times_each_philosopher_must_eat: optional, number of times each philosopher must eat before the simulation stops

## Rules
• One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
• The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
• There are also forks on the table. There are as many forks as philosophers.
• Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
• When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
• Every philosopher needs to eat and should never starve.
• Philosophers don’t speak with each other.
• Philosophers don’t know if another philosopher is about to die.
• No need to say that philosophers should avoid dying.

## Requirements
- Global variables are forbidden.
- The program must not have any data races.
- Each philosopher must have a number ranging from 1 to the number of philosophers.
- Philosopher 1 sits between philosopher 2 and philosopher N (the last one). Each philosopher n is seated between philosopher n - 1 and philosopher n + 1, with the last philosopher seated next to the first.
- Any change of status of a philosopher must be written as follows:
  - timestamp_in_ms X has taken a fork
  - timestamp_in_ms X is eating
  - timestamp_in_ms X is sleeping
  - timestamp_in_ms X is thinking
  - timestamp_in_ms X died
- A displayed state message should not be mixed with another philosopher's state message.
- A message announcing the death of a philosopher should be displayed no more than 10 ms after the death itself.
- Philosophers should avoid dying.

## Notes
- The time_to_die, time_to_eat, and time_to_sleep arguments are in milliseconds.
- The time_to_die argument is the time a philosopher can stay alive without eating.
- The number_of_times_each_philosopher_must_eat argument is optional. If all philosophers eat at least this number of times, the simulation stops.
- The simulation stops when a philosopher dies or when all philosophers have eaten at least number_of_times_each_philosopher_must_eat times.
- The simulation stops if an error occurs.
- The simulation stops if the arguments are incorrect.
- The simulation stops if the number of arguments is incorrect.
- The simulation stops if the number of philosophers is less than 2.

## Bonus Part
In the bonus part, philosophers are represented by individual processes rather than threads, and the forks are controlled using semaphores to avoid deadlocks.

## Resources
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## License
[MIT](https://choosealicense.com/licenses/mit/)
```

