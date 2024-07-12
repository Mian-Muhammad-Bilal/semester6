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
        // Get the thread ID and total number of threads
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        // Compute local sequence terms for each thread
        for (int i = thread_id + 1; i < n; i += num_threads)
        {
            // Compute the value of the sequence term
            int value = sequence[i - 1] + 3;

            // Store the local copy of the sequence term
            sequence[i] = value;
        }
    }

    // Compute the final sequence values sequentially
    for (int i = 1; i < n; i++)
    {
        sequence[i] = sequence[i - 1] + 3;
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
