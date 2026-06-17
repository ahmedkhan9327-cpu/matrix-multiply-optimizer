#ifndef MATMUL_H
#define MATMUL_H
#define MAX_N 2048
#define BLOCK_SIZE 128

extern float A[MAX_N][MAX_N];
extern float B[MAX_N][MAX_N];
extern float C[MAX_N][MAX_N];
extern float Bt[MAX_N][MAX_N];

void matmul_naive(int N);
void matmul_naive_reorder(int N);
void matmul_block(int N);
void matmul_transpose(int N);
void reset_C(int N);
void transpose_B(int N);

#endif


