#include <stdio.h>
#include <omp.h>
#define N 3
// No race condition in this code as each thread handles a unique element
void printMatrix(int mat[N][N])
{
#pragma omp parallel for
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
#pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
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
