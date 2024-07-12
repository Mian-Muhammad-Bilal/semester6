#include <stdio.h>
#include <omp.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0; // Declare sum outside the parallel region

    // Parallel computation of partial sums
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num(); // Get the thread ID
        int local_sum = 0;

        // Compute partial sum for this thread's subset of the array
        #pragma omp for
        for (int i = 0; i < 10; i++) {
            local_sum += arr[i];
        }

        // Print the partial sum computed by this thread
        printf("Thread %d computed partial sum: %d\n", thread_id, local_sum);

        // Reduction operation to compute the total sum
        #pragma omp atomic
        sum += local_sum;
    }

    printf("Total sum: %d\n", sum);

    return 0;
}