# Philosophers
<div align="center">
  <img src="https://img.shields.io/badge/norminette-passing-success"/>
  <img src="https://img.shields.io/badge/42-project-000000"/>
</div>

## 💡 About
> This project is a solution to the classic dining philosophers problem, implementing thread synchronization and mutex locks to prevent deadlocks and race conditions.

The dining philosophers problem illustrates synchronization challenges in concurrent programming. Multiple philosophers sit at a round table with a bowl of spaghetti in the center and forks between each philosopher. They must coordinate to eat, think, and sleep without starving.

## 🛠️ Usage
### Requirements
- GCC compiler
- Make
- pthread library
- Unix-based operating system

### Instructions
**1. Compiling**
```shell
$ git clone https://github.com/wdaoudi-/philosophers
$ cd philosophers
$ make
```

**2. Running the program**
```shell
$ ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## 📋 Features
### Core Features
| Feature | Description |
|---------|-------------|
| Thread Management | Each philosopher is represented by a thread |
| Mutex Implementation | Forks are protected by mutexes to prevent race conditions |
| Death Detection | Monitors philosopher status to detect starvation |
| State Management | Handles eating, sleeping, and thinking states |
| Resource Sharing | Manages fork allocation between philosophers |

## ⚙️ Implementation Details
### Architecture
- Uses POSIX threads for concurrent execution
- Implements mutex locks for resource synchronization
- Circular linked list structure for philosopher management
- Custom time management system for precise state tracking

### Technical Choices
- Written in C
- Follows 42 School's Norm
- Thread-safe printing mechanism
- Optimized fork distribution algorithm
- Deadlock prevention system

## 🚨 Error Management
- Handles invalid arguments and input validation
- Manages thread creation failures
- Proper mutex initialization and cleanup
- Memory leak prevention
- Graceful program termination

## 🧪 Testing
```shell
# Test with 4 philosophers
$ ./philo 4 410 200 200

# Test with 5 philosophers
$ ./philo 5 800 200 200

# Test with set number of meals
$ ./philo 5 800 200 200 7
```

## 📚 Resources
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Thread Synchronization](https://www.geeksforgeeks.org/thread-synchronization-in-c/)

## 🗣️ About
### Contributing
Project developed as part of the 42 school curriculum by:
- [wdaoudi-](https://github.com/wdaoudi-)

### License
This project is released under the [MIT License](https://opensource.org/licenses/MIT)

---
Made with ❤️ by wdaoudi-
