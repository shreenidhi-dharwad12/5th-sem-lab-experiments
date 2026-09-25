\# Experiment 02 --- OpenMP Matrix Multiplication



\## Parallel Computing \& GPU Lab



\### Experiment Overview



This experiment implements \*\*4000 × 4000 matrix multiplication using

OpenMP shared-memory parallelism\*\*.



The OpenMP implementation uses multiple CPU threads to divide the outer

loop of the matrix multiplication across threads. The mathematical

computation remains the same as the sequential implementation, and the

result is verified using `C\[0]\[0] = 4000.00`.



The experiment is adapted from the laboratory reference manual for:



> \*\*Matrix Multiplication using Sequential, OpenMP, MPI and CUDA\*\*



\------------------------------------------------------------------------



\## 1. Objective



To implement and execute matrix multiplication using \*\*OpenMP\*\*, compare

its execution time with the sequential CPU implementation, verify the

correctness of the result, and calculate the speedup obtained through

thread-level parallelism.



\### Problem Definition



\-   Matrix `A`: 4000 × 4000, all elements initialized to `1.0`

\-   Matrix `B`: 4000 × 4000, all elements initialized to `1.0`

\-   Matrix `C`: `A × B`

\-   Expected value of every element of `C`:



``` text

C\[i]\[j] = 1×1 + 1×1 + ... + 1×1

&#x20;        = 4000.00

```



Therefore:



``` text

C\[0]\[0] = 4000.00

```



\------------------------------------------------------------------------



\## 2. System / Environment



\### Host System



\-   Operating System: macOS

\-   Architecture: Apple Silicon / ARM64

\-   Compiler: Apple Clang

\-   OpenMP runtime: `libomp`

\-   OpenMP threads used: \*\*8\*\*



\### Compiler Verification



The installed compiler was verified using:



``` bash

gcc --version

```



The system reports Apple Clang, targeting ARM64 macOS.



> Note: On macOS, the OpenMP program was compiled using Clang together

> with Homebrew's `libomp`, rather than the Linux/WSL GCC setup

> described in the reference manual.



\------------------------------------------------------------------------



\## 3. OpenMP Setup



\### 3.1 CPU Verification



The number of logical and physical CPU cores was checked using macOS

commands:



``` bash

sysctl -n hw.logicalcpu

sysctl -n hw.physicalcpu

```



This was used to determine the CPU resources available to the OpenMP

runtime.



\### 3.2 OpenMP Runtime Installation



OpenMP support was installed using Homebrew:



``` bash

brew install libomp

```



The installation location was verified using:



``` bash

brew --prefix libomp

```



\### 3.3 Thread Configuration



Eight OpenMP threads were requested:



``` bash

export OMP\_NUM\_THREADS=8

```



The setting was verified using:



``` bash

echo $OMP\_NUM\_THREADS

```



Expected output:



``` text

8

```



\------------------------------------------------------------------------



\## 4. Working Directory



The OpenMP experiment was maintained separately from the sequential

implementation.



Directory creation:



``` bash

mkdir -p \~/parallel\_lab/openmp

cd \~/parallel\_lab/openmp

```



The main source and executable are:



``` text

matrix\_openmp.c

matrix\_openmp

```



\------------------------------------------------------------------------



\## 5. OpenMP Source Code



\### `matrix\_openmp.c`



``` c

\#include <stdio.h>

\#include <stdlib.h>

\#include <omp.h>



\#define N 4000



int main()

{

&#x20;   int i, j, k;

&#x20;   double \*A, \*B, \*C;

&#x20;   double start, end;



&#x20;   A = (double \*)malloc(N \* N \* sizeof(double));

&#x20;   B = (double \*)malloc(N \* N \* sizeof(double));

&#x20;   C = (double \*)malloc(N \* N \* sizeof(double));



&#x20;   if (A == NULL || B == NULL || C == NULL)

&#x20;   {

&#x20;       printf("Memory allocation failed\\n");

&#x20;       return 1;

&#x20;   }



&#x20;   for (i = 0; i < N; i++)

&#x20;   {

&#x20;       for (j = 0; j < N; j++)

&#x20;       {

&#x20;           A\[i \* N + j] = 1.0;

&#x20;           B\[i \* N + j] = 1.0;

&#x20;           C\[i \* N + j] = 0.0;

&#x20;       }

&#x20;   }



&#x20;   start = omp\_get\_wtime();



&#x20;   #pragma omp parallel for private(j, k)

&#x20;   for (i = 0; i < N; i++)

&#x20;   {

&#x20;       for (j = 0; j < N; j++)

&#x20;       {

&#x20;           for (k = 0; k < N; k++)

&#x20;           {

&#x20;               C\[i \* N + j] +=

&#x20;                   A\[i \* N + k] \*

&#x20;                   B\[k \* N + j];

&#x20;           }

&#x20;       }

&#x20;   }



&#x20;   end = omp\_get\_wtime();



&#x20;   printf("OpenMP Matrix Multiplication Completed\\n");

&#x20;   printf("Matrix Size = %d x %d\\n", N, N);

&#x20;   printf("Number of Threads Used = %d\\n", omp\_get\_max\_threads());

&#x20;   printf("Execution Time = %f seconds\\n", end - start);

&#x20;   printf("Verification C\[0]\[0] = %.2f\\n", C\[0]);



&#x20;   free(A);

&#x20;   free(B);

&#x20;   free(C);



&#x20;   return 0;

}

```



\------------------------------------------------------------------------



\## 6. Important OpenMP Components



\### OpenMP Header



``` c

\#include <omp.h>

```



Provides the OpenMP functions and runtime interface.



\### Parallel Loop



``` c

\#pragma omp parallel for private(j, k)

```



This divides the iterations of the outer `i` loop among multiple OpenMP

threads.



\### OpenMP Timing



``` c

start = omp\_get\_wtime();

```



and:



``` c

end = omp\_get\_wtime();

```



The difference gives the OpenMP computation time.



\### Thread Count



``` c

omp\_get\_max\_threads()

```



reports the maximum number of OpenMP threads available according to the

runtime configuration.



\------------------------------------------------------------------------



\## 7. Compilation



Because the experiment was performed on macOS using Apple Silicon,

OpenMP was compiled using Clang and Homebrew's `libomp`.



\### Compilation Command



``` bash

clang -O2 -Xpreprocessor -fopenmp \\

\-I/opt/homebrew/opt/libomp/include \\

\-L/opt/homebrew/opt/libomp/lib \\

\-lomp \\

matrix\_openmp.c \\

\-o matrix\_openmp

```



\### Explanation



\-   `clang` --- Apple Clang compiler

\-   `-O2` --- enables compiler optimization

\-   `-Xpreprocessor -fopenmp` --- enables OpenMP preprocessing

\-   `-I.../include` --- locates OpenMP header files

\-   `-L.../lib` --- locates the OpenMP library

\-   `-lomp` --- links the OpenMP runtime

\-   `matrix\_openmp.c` --- source file

\-   `-o matrix\_openmp` --- generated executable



Compilation completed successfully.



\------------------------------------------------------------------------



\## 8. Executable Verification



The generated files were checked using:



``` bash

ls -lh

```



Expected project files:



``` text

matrix\_openmp.c

matrix\_openmp

```



The executable was successfully created and used for the experiment.



\------------------------------------------------------------------------



\## 9. OpenMP Execution



The program was executed using:



``` bash

./matrix\_openmp

```



The OpenMP runtime was configured for eight threads.



\### Actual Execution Output



``` text

OpenMP Matrix Multiplication Completed



Matrix Size = 4000 x 4000



Number of Threads Used = 8



Execution Time = 82.747345 seconds



Verification C\[0]\[0] = 4000.00

```



\------------------------------------------------------------------------



\## 10. CPU Utilization Monitoring



CPU utilization was monitored using `htop` while the OpenMP matrix

multiplication was running.



Command:



``` bash

htop

```



This provided a visual indication of CPU activity during the

multi-threaded computation.



\------------------------------------------------------------------------



\## 11. Sequential Baseline



The OpenMP speedup was calculated using the actual sequential execution

time obtained on the same Mac system.



\### Sequential Result



``` text

Matrix Size = 4000 x 4000

Execution Time = 246.610556 seconds

C\[0]\[0] = 4000.00

```



\### OpenMP Result



``` text

Matrix Size = 4000 x 4000

Number of Threads Used = 8

Execution Time = 82.747345 seconds

C\[0]\[0] = 4000.00

```



\------------------------------------------------------------------------



\## 12. Speedup Calculation



The speedup formula is:



``` text

Speedup = Sequential Execution Time / OpenMP Execution Time

```



Using the actual measured values:



``` text

Speedup = 246.610556 / 82.747345

&#x20;       ≈ 2.98×

```



\### Result



\*\*OpenMP Speedup = 2.98×\*\*



This means that, for this particular 4000 × 4000 workload on the tested

Mac system, the measured OpenMP execution time was approximately

one-third of the measured sequential execution time.



\------------------------------------------------------------------------



\## 13. Performance Comparison



&#x20; Implementation     Execution Time Resources                Verification   Speedup

&#x20; ---------------- ---------------- ---------------------- -------------- ---------

&#x20; Sequential           246.610556 s Single CPU execution          4000.00     1.00×

&#x20; OpenMP                82.747345 s 8 CPU threads                 4000.00     2.98×



All implementations produced the expected verification value:



``` text

C\[0]\[0] = 4000.00

```



\------------------------------------------------------------------------



\## 14. Why OpenMP Is Faster



The sequential implementation performs the matrix multiplication using

one CPU execution flow.



OpenMP introduces thread-level parallelism by distributing iterations of

the outer matrix row loop across multiple CPU threads.



Conceptually:



``` text

Sequential:



i = 0

i = 1

i = 2

...

i = 3999

&#x20;       ↓

one execution flow

```



With OpenMP:



``` text

&#x20;                4000 rows

&#x20;                    │

&#x20;         ┌──────────┼──────────┐

&#x20;         ↓          ↓          ↓

&#x20;      Thread 1   Thread 2   ... Thread 8

&#x20;         │          │             │

&#x20;       rows       rows          rows

&#x20;         └──────────┼─────────────┘

&#x20;                    ↓

&#x20;                 Matrix C

```



The matrices remain in shared memory while different threads process

different outer-loop iterations.



\------------------------------------------------------------------------



\## 15. Verification



The correctness of the multiplication was verified using:



``` text

C\[0]\[0] = 4000.00

```



Since every element of both input matrices is `1.0`, each output element

is the sum of 4000 products of `1.0 × 1.0`.



Therefore:



``` text

C\[0]\[0] = 4000.00

```



The expected result was obtained successfully.



\------------------------------------------------------------------------





\## 16. Experiment Workflow



``` text

CPU Verification

&#x20;      ↓

OpenMP Runtime Setup

&#x20;      ↓

Set OMP\_NUM\_THREADS = 8

&#x20;      ↓

Create OpenMP Source

&#x20;      ↓

Compile with OpenMP Support

&#x20;      ↓

Execute 4000 × 4000 Matrix Multiplication

&#x20;      ↓

Monitor CPU Utilization

&#x20;      ↓

Verify C\[0]\[0] = 4000.00

&#x20;      ↓

Record Execution Time

&#x20;      ↓

Compare with Sequential Baseline

&#x20;      ↓

Calculate Speedup

```



\------------------------------------------------------------------------



\## 17. Final Result



\### OpenMP Matrix Multiplication



``` text

Matrix Size          : 4000 × 4000

Number of Threads    : 8

Execution Time       : 82.747345 seconds

Verification         : C\[0]\[0] = 4000.00

Speedup              : 2.98×

```



\### Conclusion



The 4000 × 4000 matrix multiplication was successfully implemented using

OpenMP shared-memory parallelism on an Apple Silicon Mac. Eight OpenMP

threads were used to parallelize the outer matrix-multiplication loop.

The program completed successfully with the expected verification value

of `4000.00`.



Compared with the measured sequential execution time of `246.610556`

seconds, the OpenMP implementation required `82.747345` seconds and

achieved a measured speedup of approximately `2.98×`.



\------------------------------------------------------------------------



\## 18. Reference



\*\*Laboratory Manual:\*\*\\

\*Matrix Multiplication using Sequential, OpenMP, MPI and CUDA\*



The manual defines the 4000 × 4000 workload, OpenMP implementation,

thread configuration, execution workflow, verification method,

screenshot requirements, and speedup formula used in this experiment.



