#include <stdio.h>

#define N 512

float A[N][N];
float B[N][N];
float C[N][N];

int main(void) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 3;
            B[i][j] = 4;
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("C[0][0] = %f\n", C[0][0]);
    return 0;
}



