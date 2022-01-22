# Table of contents
1. [Introduction](#introduction)
2. [Multithreading](#Multithreading)
3. [Mutex](#mutex)
4. [Multithreading issues](#issues)
	- [Data races](#races)
	- [Deadlocks](#dead)

# Introduction <a name="introduction"></a>
Philosophers is a project developped by myself in ecole 42. The project was developed in C and it was done in around two weeks. The project introduces multithreading programmation and its issues.
The goal of the project is to find a solution to the well known [dining philosophers problem](https://www.youtube.com/watch?v=NbwbQQB7xNQ).

# Multithreading <a name="Multithreading"></a>
A Thread is a sequence of programated instructions, they usually are components of a process.

Threads can be executed concurently (at the same time), and they share the same memory space.

Multithreading programmation is also refered to as paralel programming whereas your computer divide its power into parts in order to run code at the exact same time. If the computer has a single processor, it will use tricks to switch between threads and create the illusion of paralelism. In order to use multithreading in C, we use the pthread library.
```shell
int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
int pthread_join(pthread_t thread, void **retval);
```
The threads are created using the pthread_create() function, and will execute the code in the start_routine function. While the threads are created, the "main thread" of the program will keep on executing code. In order for the program to wait for the threads to finish their execution, we use pthread_join.  

# Mutex <a name="mutex"></a>
A mutex is a [synchronization primitives](https://stackoverflow.com/questions/8017507/definition-of-synchronization-primitive/8017629) (synchronization primitives are simple software mechanisms usually given by the operating system to its users for the purposes of supporting thread or process synchronization. They're usually built using lower level mechanisms (e.g. atomic operations, memory barriers, spinlocks, context switches etc)). A mutex works like a lock, it can be locked, blocking the access to part a of code to other threads, and unlocked, leaving its place .
```shell
pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
Mutex are initiated, locked and unlocked using those functions. Once unlocked, it is safe to destroy the mutex.

# Multithreading issues <a name="issues"></a>
While multithreading programmation is useful in [many situations](https://totalview.io/blog/multithreading-multithreaded-applications), it also comes with a few potential issues.
1. ### Data races <a name="races"></a>
[Data races](https://www.modernescpp.com/index.php/race-condition-versus-data-race): A data race is a situation, in which at least two threads access a shared variable at the same time. At least one thread tries to modify the variable. Some operations refered to as **atomic**, are free of data races risks, as they cannot happen at the same time (the mutex are an example of atomic operation). The way to avoid facing this issue is using mutex.

2. ### Deadlocks <a name="dead"></a>
A deadlock is an issue that can happen when using mutex. A deadlock hapens if the current thread is waiting for another to unlock its mutex, while this other thread is waiting for the current thread to unlock its mutex to proceed. This leads the program to be stuck in a neverending loop. The way to fix it is to manipulate the code in order to never face the problem (use usleep() to make threads lock at different times).
