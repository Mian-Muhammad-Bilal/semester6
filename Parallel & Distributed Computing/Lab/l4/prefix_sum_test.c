#include <stdio.h>
#include <omp.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int prefix_sum[10];

    prefix_sum[0] = arr[0]; // First element remains the same

    #pragma omp parallel
    {
        int partial_sum = 0;

        #pragma omp for
        for (int i = 1; i < 10; i++) {
            // Compute partial sum for this thread's subset of the array
            partial_sum += arr[i];
            prefix_sum[i] = partial_sum;
        }

        #pragma omp for
        for (int i = 1; i < 10; i++) {
            // Update prefix_sum with the partial sum computed by each thread
            prefix_sum[i] += prefix_sum[i - 1];
        }
    }

    printf("Prefix sum: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", prefix_sum[i]);
    }
    printf("\n");

    return 0;
}
