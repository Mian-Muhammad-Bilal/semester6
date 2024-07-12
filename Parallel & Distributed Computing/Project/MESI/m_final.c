#include <omp.h>
#include <stdio.h>

#define NUM_PROCS 4
#define ARRAY_SIZE 100

// Define cache line states
#define INVALID 0
#define SHARED 1
#define MODIFIED 2
#define EXCLUSIVE 3

int main()
{
    // Array to be shared among processors
    int shared_array[ARRAY_SIZE] = {0}; // Initialize main memory with zeros

    // Cache arrays for each processor
    int cache[NUM_PROCS][ARRAY_SIZE];
    int cache_state[NUM_PROCS][ARRAY_SIZE]; // Cache line state

    // Initialize cache states to INVALID
    for (int i = 0; i < NUM_PROCS; ++i)
    {
        for (int j = 0; j < ARRAY_SIZE; ++j)
        {
            cache_state[i][j] = INVALID;
        }
    }

    // Parallel section simulating multiple processors accessing shared data
#pragma omp parallel num_threads(NUM_PROCS)
    {
        int thread_id = omp_get_thread_num();

        // Each processor accesses a portion of the shared array
        for (int i = thread_id * (ARRAY_SIZE / NUM_PROCS); i < (thread_id + 1) * (ARRAY_SIZE / NUM_PROCS); ++i)
        {
            // Check cache state
            if (cache_state[thread_id][i] == INVALID)
            {
                // Read data from main memory into cache
                cache[thread_id][i] = shared_array[i];
                cache_state[thread_id][i] = EXCLUSIVE; // Change state to exclusive
            }
            else if (cache_state[thread_id][i] == SHARED)
            {
                // Read data from shared state, use cache value
                // No need to update cache state
            }

            // Perform some computation on the data (e.g., increment by thread ID)
            cache[thread_id][i] += thread_id;
            cache_state[thread_id][i] = MODIFIED; // Change state to modified

            // Update shared array if cache state is MODIFIED
            shared_array[i] = cache[thread_id][i]; // updating the main memory
        }
    }

    // Print final cache states
    printf("Final cache states:\n");
    for (int i = 0; i < NUM_PROCS; ++i)
    {
        printf("Processor %d:\n", i);
        for (int j = 0; j < ARRAY_SIZE; ++j)
        {
            printf("%d ", cache_state[i][j]);
        }
        printf("\n");
    }

    return 0;
}
