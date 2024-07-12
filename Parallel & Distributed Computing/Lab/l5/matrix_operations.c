#include <stdio.h>
#include <omp.h>

#define N 3

void printMatrix(int mat[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num();
        for (int j = 0; j < N; j++) {
            printf("Thread %d: %d ", thread_id, mat[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int A[N][N], int B[N][N], int C[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num();
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[i][j];
            printf("Thread %d: C[%d][%d] = %d\n", thread_id, i, j, C[i][j]);
        }
    }
}

int main() {
    int A[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[N][N] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int C[N][N];

    addMatrices(A, B, C);

    printf("Matrix A:\n");
    printMatrix(A);

    printf("\nMatrix B:\n");
    printMatrix(B);

    printf("\nMatrix C (A + B):\n");
    printMatrix(C);

    return 0;
}
