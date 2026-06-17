#include <stdio.h>
#include <time.h>
#include "matmul.h"

int main(void) {
    int sizes[] = {256, 512, 1024, 2048};
    int num_sizes = 4;

    void (*functions[])(int) = {matmul_naive, matmul_naive_reorder, matmul_block, matmul_transpose};
    const char* names[] = {"Naive", "Reordered", "Blocked", "Transposed"};
    int num_functions = 4;

    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            A[i][j] = 3;
            B[i][j] = 4;
        }
    }

    struct timespec start, end;

    for (int s = 0; s < num_sizes; s++) {
        int size = sizes[s];
        printf("=== N = %d ===\n", size);

        for (int i = 0; i < num_functions; i++) {
            reset_C(size);

            if (i == 3) {
                transpose_B(size);
            }

            clock_gettime(CLOCK_MONOTONIC, &start);
            functions[i](size);
            clock_gettime(CLOCK_MONOTONIC, &end);

            double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

            printf("%s: C[0][0] = %f, Time: %f seconds\n", names[i], C[0][0], elapsed);
        }
    }
    return 0;
}