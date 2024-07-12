#include <stdio.h>
#include <omp.h>
int main()
{
    int n;
    printf("Enter the number of terms in the sequence: ");
    scanf("%d", &n);
    // Initialize array to store sequence terms
    int sequence[n];
    // Initialize the first term of the sequence
    int start_value;
    printf("Enter the starting value of the sequence: ");
    scanf("%d", &start_value);
    sequence[0] = start_value;
// Parallel computation of local sequence terms
#pragma omp parallel
    {
        // Each thread computes a local sequence segment
        int thread_id = omp_get_thread_num();
        int local_start = (n * thread_id) / omp_get_num_threads();
        int local_end = (n * (thread_id + 1)) / omp_get_num_threads();
        for (int i = local_start + 1; i < local_end; i++)
        {
// Use a critical section to ensure serialized updates
#pragma omp critical
            {
                sequence[i] = sequence[i - 1] + 3;
            }
        }
    }
    // Print the sequence
    printf("Sequence: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");
    return 0;
}
