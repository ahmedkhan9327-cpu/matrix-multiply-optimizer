#include <stdio.h>
#include <time.h>
#include "matmul.h"

float A[MAX_N][MAX_N];
float B[MAX_N][MAX_N];
float C[MAX_N][MAX_N];
float Bt[MAX_N][MAX_N];

void matmul_naive(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_naive_reorder(int N) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matmul_block(int N) {
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

void matmul_transpose(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * Bt[j][k];
            }
        }
    }
}

void reset_C(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }
}

void transpose_B(int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Bt[j][i] = B[i][j];
        }
    }
}



