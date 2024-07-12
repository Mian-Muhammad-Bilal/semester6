#include <stdio.h>
#include <string.h>
#include <omp.h>

#define NUM_WORDS 100000
#define NUM_VOWELS 10
#define NUM_THREADS 4
#define SEGMENT_SIZE (NUM_WORDS / NUM_THREADS)

char text[NUM_WORDS][100]; // assuming each word has at most 100 characters

int main()
{
    int global_counts[NUM_VOWELS] = {0}; // counts for vowels a, A, e, E, i, I, o, O, u, U
    char vowels[NUM_VOWELS] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

    // Initialize text array with dummy data for demonstration
    for (int i = 0; i < NUM_WORDS; i++)
    {
        strcpy(text[i], "This is a sample text with vowels AEIOU aeiou");
    }

    int local_counts[NUM_THREADS][NUM_VOWELS] = {0};

#pragma omp parallel num_threads(NUM_THREADS)
    {
        int id = omp_get_thread_num();
        int start = id * SEGMENT_SIZE;
        int end = (id + 1) * SEGMENT_SIZE;

        for (int i = start; i < end; i++)
        {
            for (int j = 0; j < strlen(text[i]); j++)
            {
                char c = text[i][j];
                for (int k = 0; k < NUM_VOWELS; k++)
                {
                    if (c == vowels[k])
                    {
                        local_counts[id][k]++;
                    }
                }
            }
        }
    }

    // Reduce phase: aggregate local counts into global counts
    for (int i = 0; i < NUM_THREADS; i++)
    {
        for (int k = 0; k < NUM_VOWELS; k++)
        {
            global_counts[k] += local_counts[i][k];
        }
    }

    printf("Vowel counts:\n");
    for (int k = 0; k < NUM_VOWELS; k++)
    {
        printf("%c: %d\n", vowels[k], global_counts[k]);
    }

    return 0;
}
