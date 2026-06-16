#include <stdio.h>
#include <time.h>

#define N 512

float A[N][N];
float B[N][N];
float C[N][N];

struct timespec start, end;

// Matrix-multiplier naive implementation
void matmul_naive(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix-multiplier loop reorder i-k-j
void matmul_naive_reorder(void) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Matrix-multiplier blocking implementation
void matmul_block(void) {

}

// Resets all values of matrix C
void reset_C(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
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
    printf("C[0][0] = %f\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    reset_C();

    clock_gettime(CLOCK_MONOTONIC, &start);
    matmul_naive_reorder();
    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Naive implementation reorder:\n");
    printf("C[0][0] = %f\n", C[0][0]);
    printf("Time: %f seconds\n", elapsed);

    reset_C();

    return 0;
}



