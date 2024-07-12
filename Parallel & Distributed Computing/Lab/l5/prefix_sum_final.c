#include <stdio.h>
#include <omp.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int prefix_sum[10];

    prefix_sum[0] = arr[0]; // First element remains the same

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        // Compute local prefix sum for this thread
        int local_sum = arr[0]; // Initialize with the first element
        for (int i = 1; i < 10; i++) {
            local_sum += arr[i];
            prefix_sum[i] = local_sum; // Store the local prefix sum
        }
    }

    printf("Prefix sum: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", prefix_sum[i]);
    }
    printf("\n");

    return 0;
}
