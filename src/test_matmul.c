#include <assert.h>
#include "matmul.h"
#include <stdio.h>

void test_correctness(int N) {
    float expected_val = 3.0f * 4.0f * N;

    reset_C(N);
    matmul_naive(N);
    assert(C[0][0] == expected_val);

    reset_C(N);
    matmul_naive_reorder(N);
    assert(C[0][0] == expected_val);

    reset_C(N);
    matmul_block(N);
    assert(C[0][0] == expected_val);

    reset_C(N);
    transpose_B(N);
    matmul_transpose(N);
    assert(C[0][0] == expected_val);

    printf("All correctness tests passed, %d\n", N);
}

int main(void) {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            A[i][j] = 3;
            B[i][j] = 4;
        }
    }

    int sizes[] = {256, 512, 1024, 2048};
    for (int s = 0; s < 4; s++) {
        test_correctness(sizes[s]);
    }

    return 0;
}