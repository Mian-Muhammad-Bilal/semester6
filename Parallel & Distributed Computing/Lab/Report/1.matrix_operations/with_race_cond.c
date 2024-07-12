#include <stdio.h>
#include <omp.h>
#define N 3
void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
void addMatrices(int A[N][N], int B[N][N], int C[N][N])
{
    int sum = 0;
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
            // Race condition: multiple threads update 'sum' concurrently
            sum += C[i][j];
        }
    }
    printf("Sum of all elements in C: %d\n", sum);
}

int main()
{
    int A[N][N] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int B[N][N] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
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
