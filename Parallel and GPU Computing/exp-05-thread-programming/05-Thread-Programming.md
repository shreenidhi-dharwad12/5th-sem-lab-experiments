\# EXP-05 — Thread Programming Using Pthreads and OpenMP



> \*\*Thread Programming, Synchronization, and Performance Comparison Using Pthreads and OpenMP\*\*



!\[Pthreads](https://img.shields.io/badge/Pthreads-Thread%20Programming-blue)

!\[OpenMP](https://img.shields.io/badge/OpenMP-Parallel%20Programming-green)

!\[Language](https://img.shields.io/badge/Language-C-orange)

!\[Platform](https://img.shields.io/badge/Platform-Ubuntu%20Linux-yellow)



\---



\## 1. Aim



To implement and study thread programming using \*\*POSIX Threads (Pthreads)\*\* and \*\*OpenMP\*\*, demonstrate thread creation, synchronization, race conditions, critical sections, barriers, and compare the performance of sequential, Pthreads, and OpenMP implementations.



\---



\## 2. Objectives



\* Create and execute threads using Pthreads.

\* Create multiple threads and pass data to threads.

\* Perform parallel array summation using threads.

\* Demonstrate a race condition.

\* Resolve race conditions using a mutex.

\* Create parallel programs using OpenMP.

\* Perform parallel reduction using OpenMP.

\* Demonstrate race conditions and critical sections in OpenMP.

\* Synchronize threads using an OpenMP barrier.

\* Compare sequential, Pthreads, and OpenMP execution performance.



\---



\# 3. Pthreads Programming



Pthreads (POSIX Threads) is a standard thread programming library used in C/C++ on Unix-like operating systems.



The Pthreads programs implemented in this experiment are:



1\. Basic thread creation

2\. Multiple thread creation

3\. Parallel array sum

4\. Race condition

5\. Mutex synchronization



\---



\## 3.1 Basic Thread Creation



\### Program



\*\*File:\*\* `code/pthread/thread1.c`



The program creates a single thread using `pthread\_create()` and waits for it using `pthread\_join()`.



\### Important Functions



\* `pthread\_create()` — creates a new thread.

\* `pthread\_join()` — waits for a thread to finish.



\### Compilation



```bash

gcc thread1.c -o thread1 -pthread

```



\### Execution



```bash

./thread1

```



\### Result



The program displays a message from the created thread followed by a message from the main thread.



\### Output



!\[Thread 1 Result](screenshots/pthread/01-thread1-result.png)



\---



\## 3.2 Multiple Thread Creation



\### Program



\*\*File:\*\* `code/pthread/thread2.c`



The program creates \*\*4 threads\*\*. Each thread receives a unique thread ID and prints its ID.



\### Compilation



```bash

gcc thread2.c -o thread2 -pthread

```



\### Execution



```bash

./thread2

```



\### Result



Four threads execute and print their thread IDs. The main thread waits for all threads to complete.



\### Output



!\[Thread 2 Result](screenshots/pthread/02-thread2-result.png)



> \*\*Note:\*\* Thread output order may vary because thread execution is concurrent.



\---



\## 3.3 Parallel Array Summation Using Pthreads



\### Program



\*\*File:\*\* `code/pthread/thread\_sum.c`



The array contains 8 elements and is divided among 4 threads.



Each thread calculates a \*\*partial sum\*\* and the main thread combines the partial sums to obtain the total sum.



\### Array



```text

10 20 30 40 50 60 70 80

```



\### Compilation



```bash

gcc thread\_sum.c -o thread\_sum -pthread

```



\### Execution



```bash

./thread\_sum

```



\### Result



Each thread calculates its partial sum and the final total sum is calculated by the main thread.



\### Output



!\[Thread Sum Result](screenshots/pthread/03-thread-sum-result.png)



\---



\## 3.4 Race Condition Using Pthreads



\### Program



\*\*File:\*\* `code/pthread/race.c`



The program uses 4 threads to increment a shared counter.



Each thread performs:



```text

100000 increments

```



The expected value is:



```text

4 × 100000 = 400000

```



However, because multiple threads access the shared counter without synchronization, a \*\*race condition\*\* can occur.



\### Compilation



```bash

gcc race.c -o race -pthread

```



\### Execution



```bash

./race

```



\### Result



The final counter value may differ from the expected value because multiple threads can simultaneously modify the shared variable.



\### Output



!\[Race Condition Result](screenshots/pthread/04-race-result.png)



\---



\## 3.5 Mutex Synchronization



\### Program



\*\*File:\*\* `code/pthread/mutex.c`



A mutex is used to protect the shared counter.



Only one thread can enter the critical section at a time.



\### Important Functions



```c

pthread\_mutex\_lock()

pthread\_mutex\_unlock()

pthread\_mutex\_init()

pthread\_mutex\_destroy()

```



\### Compilation



```bash

gcc mutex.c -o mutex -pthread

```



\### Execution



```bash

./mutex

```



\### Result



The mutex prevents simultaneous access to the shared counter, producing the correct final value.



\### Output



!\[Mutex Result](screenshots/pthread/05-mutex-result.png)



\---



\# 4. OpenMP Programming



OpenMP is an API used for shared-memory parallel programming in C, C++, and Fortran.



The OpenMP programs implemented are:



1\. Basic parallel region

2\. Parallel array summation using reduction

3\. Race condition

4\. Critical section

5\. Barrier synchronization



\---



\## 4.1 Basic OpenMP Parallel Program



\### Program



\*\*File:\*\* `code/openmp/omp1.c`



The program creates a parallel region using:



```c

\#pragma omp parallel

```



Each thread prints its thread ID and the total number of threads.



\### Compilation



```bash

gcc omp1.c -o omp1 -fopenmp

```



\### Execution



```bash

./omp1

```



\### Result



Multiple OpenMP threads execute the parallel region.



\### Output



!\[OpenMP Basic Result](screenshots/openmp/01-omp1-result.png)



> \*\*Note:\*\* The order of thread output may vary between executions.



\---



\## 4.2 OpenMP Parallel Sum Using Reduction



\### Program



\*\*File:\*\* `code/openmp/omp\_sum.c`



The program calculates the sum of an array using:



```c

\#pragma omp parallel for reduction(+:total\_sum)

```



The reduction operation safely combines the partial results from different threads.



\### Compilation



```bash

gcc omp\_sum.c -o omp\_sum -fopenmp

```



\### Execution



```bash

./omp\_sum

```



\### Result



The total sum of the array is calculated using OpenMP parallelism.



\### Output



!\[OpenMP Sum Result](screenshots/openmp/02-omp-sum-result.png)



\---



\## 4.3 OpenMP Race Condition



\### Program



\*\*File:\*\* `code/openmp/omp\_race.c`



Four OpenMP threads increment a shared counter without synchronization.



\### Expected Value



```text

4 × 100000 = 400000

```



Because the shared variable is accessed concurrently, a race condition can occur.



\### Compilation



```bash

gcc omp\_race.c -o omp\_race -fopenmp

```



\### Execution



```bash

./omp\_race

```



\### Result



The final value may be different from the expected value because multiple threads update the same variable without synchronization.



\### Output



!\[OpenMP Race Result](screenshots/openmp/03-omp-race-result.png)



\---



\## 4.4 OpenMP Critical Section



\### Program



\*\*File:\*\* `code/openmp/omp\_critical.c`



The program uses:



```c

\#pragma omp critical

```



to ensure that only one thread updates the shared counter at a time.



\### Compilation



```bash

gcc omp\_critical.c -o omp\_critical -fopenmp

```



\### Execution



```bash

./omp\_critical

```



\### Result



The critical section protects the shared counter and ensures synchronized access.



\### Output



!\[OpenMP Critical Result](screenshots/openmp/04-omp-critical-result.png)



\---



\## 4.5 OpenMP Barrier Synchronization



\### Program



\*\*File:\*\* `code/openmp/omp\_barrier.c`



The program demonstrates barrier synchronization using:



```c

\#pragma omp barrier

```



The threads execute \*\*Stage 1\*\*, wait at the barrier, and then proceed to \*\*Stage 2\*\*.



\### Compilation



```bash

gcc omp\_barrier.c -o omp\_barrier -fopenmp

```



\### Execution



```bash

./omp\_barrier

```



\### Result



The barrier ensures that all threads reach the synchronization point before any thread proceeds to Stage 2.



\### Output



!\[OpenMP Barrier Result](screenshots/openmp/05-omp-barrier-result.png)



\---



\# 5. Performance Comparison



The experiment also compares the execution time of:



\* Sequential execution

\* Pthreads parallel execution

\* OpenMP parallel execution



The programs perform a large numerical summation with:



```text

N = 1,000,000,000

```



\---



\## 5.1 Sequential Execution



\### Program



\*\*File:\*\* `code/performance/sequential.c`



The program performs the summation sequentially using a single execution flow.



\### Compilation



```bash

gcc sequential.c -o sequential

```



\### Execution



```bash

./sequential

```



\### Output



!\[Sequential Performance](screenshots/performance/01-sequential-result.png)



\---



\## 5.2 Pthreads Performance



\### Program



\*\*File:\*\* `code/performance/pthread\_perf.c`



The program divides the computation among a user-specified number of Pthreads.



The program accepts:



```text

Number of threads: 1–32

```



Each thread calculates a partial sum, and the main thread combines the results.



\### Compilation



```bash

gcc pthread\_perf.c -o pthread\_perf -pthread

```



\### Execution



```bash

./pthread\_perf

```



\### Output



!\[Pthreads Performance](screenshots/performance/02-pthread-performance.png)



\---



\## 5.3 OpenMP Performance



\### Program



\*\*File:\*\* `code/performance/omp\_perf.c`



The program performs the same computation using an OpenMP parallel loop with reduction.



The number of threads can be specified by the user.



\### Compilation



```bash

gcc omp\_perf.c -o omp\_perf -fopenmp

```



\### Execution



```bash

./omp\_perf

```



\### Output



!\[OpenMP Performance](screenshots/performance/03-openmp-performance.png)



\---



\# 6. Thread Synchronization Concepts Demonstrated



| Concept             | Pthreads           | OpenMP                     |

| ------------------- | ------------------ | -------------------------- |

| Thread Creation     | `pthread\_create()` | `#pragma omp parallel`     |

| Waiting for Threads | `pthread\_join()`   | Parallel region completion |

| Race Condition      | `race.c`           | `omp\_race.c`               |

| Mutual Exclusion    | Mutex              | Critical section           |

| Synchronization     | `pthread\_join()`   | `barrier`                  |

| Parallel Sum        | `thread\_sum.c`     | `reduction`                |

| Performance Testing | `pthread\_perf.c`   | `omp\_perf.c`               |



\---



\# 7. Important Observations



\* Multiple threads can execute concurrently.

\* Thread execution order is not guaranteed.

\* Shared variables can cause race conditions.

\* Mutexes provide mutual exclusion in Pthreads.

\* OpenMP critical sections provide synchronized access to shared data.

\* OpenMP reduction s



