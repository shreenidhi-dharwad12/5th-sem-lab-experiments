Experiment 01 - Sequential Matrix Multiplication

Aim

To implement matrix multiplication sequentially using C and measure the execution time for a large matrix.

Problem Statement

Perform multiplication of two 4000 x 4000 matrices using a sequential C program and verify the correctness of the result.

Technology Used

• Language: C
• Compiler: GCC
• Matrix Size: 4000 x 4000
• Execution Environment: Ubuntu / Linux

Algorithm

1. Initialize matrices A and B.
2. Initialize all elements of A and B to 1.
3. Multiply the matrices using three nested loops.
4. Store the result in matrix C.
5. Measure the execution time.
6. Verify the result using C[0][0].

Matrix Multiplication

Each element of the result matrix is calculated by multiplying one row of matrix A with one column of matrix B and adding the products.

Compilation

gcc -O2 matrix_sequential.c -o matrix_sequential

Execution

./matrix_sequential

Result

Matrix Size = 4000 x 4000

Execution Time = 344.181180 seconds

Verification C[0][0] = 4000.00

Verification

Since every element of matrices A and B is initialized to 1:

C[0][0] = 1*1 + 1*1 + ... + 1*1

There are 4000 terms.

Therefore:

C[0][0] = 4000.00

The result is verified successfully.

Complexity

• Time Complexity: O(N^3)
• Space Complexity: O(N^2)

For N = 4000, sequential matrix multiplication requires a large number of operations.

Conclusion

The sequential implementation successfully performed multiplication of two 4000 x 4000 matrices. The execution time was 344.181180 seconds, and the result was verified using C[0][0] = 4000.00.
