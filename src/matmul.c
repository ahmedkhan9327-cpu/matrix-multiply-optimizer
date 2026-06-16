#include <stdio.h>
#include <time.h>

#define N 1024
#define BLOCK_SIZE 128

int A[N][N];
int B[N][N];
int C[N][N];
int Bt[N][N];

struct timespec start, end;

// Matrix-multiplier naive
void matmul_naive(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix-multiplier loop reorder
void matmul_naive_reorder(void) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix-multiplier blocking
void matmul_block(void) {
    for (int i0 = 0; i0 < N; i0 += BLOCK_SIZE) {
        for (int j0 = 0; j0 < N; j0 += BLOCK_SIZE) {
            for (int k0 = 0; k0 < N; k0 += BLOCK_SIZE) {
                for (int i = i0; i < i0 + BLOCK_SIZE; i++) {
                    for (int k = k0; k < k0 + BLOCK_SIZE; k++) {
                        for (int j = j0; j < j0 + BLOCK_SIZE; j++) {
                            C[i][j] += A[i][k] * B[k][j];
                         }
                    }
                }
            }
        }
    }
}

// Matrix-multiplier transpose
void matmul_transpose(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * Bt[j][k];
            }
        }
    }
}

// Resets values of matrix C
void reset_C(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }
}

// Tranposes matrix B
void transpose_B(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Bt[j][i] = B[i][j];
        }
    }
}

int main(void) {
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 3;
            B[i][j] = 4;
            C[i][j] = 0;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_naive();
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Naive implementation:\n");
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    reset_C();

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_naive_reorder();
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Naive implementation reorder:\n");
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    reset_C();

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_block();
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Block implementation:\n");
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    reset_C();

    transpose_B();

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_transpose();
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Transpose implementation:\n");
    printf("C[0][0] = %d\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    return 0;
}



