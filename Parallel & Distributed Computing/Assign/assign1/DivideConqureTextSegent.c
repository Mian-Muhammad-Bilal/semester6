#include <stdio.h>
#include <string.h>
#include <omp.h>

#define NUM_VOWELS 10
#define NUM_THREADS 4
#define MAX_WORD_LENGTH 100
#define NUM_WORDS 1

int main()
{
    int counts[NUM_VOWELS] = {0}; // counts for vowels a, A, e, E, i, I, o, O, u, U
    char vowels[NUM_VOWELS] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

    // Open the file for reading
    FILE *file = fopen("sample.txt", "r");
    if (!file)
    {
        perror("Unable to open file");
        return 1;
    }

    // Read the words from the file into the text array
    char word[MAX_WORD_LENGTH];
    char text[NUM_WORDS][MAX_WORD_LENGTH];
    int num_words = 0;

    while (fscanf(file, "%99s", word) == 1 && num_words < NUM_WORDS)
    {
        strcpy(text[num_words], word);
        num_words++;
    }

    fclose(file);

#pragma omp parallel num_threads(NUM_THREADS)
    {
        int local_counts[NUM_VOWELS] = {0};
        int id = omp_get_thread_num();
        int start = id * (num_words / NUM_THREADS);
        int end = (id + 1) * (num_words / NUM_THREADS);
        if (id == NUM_THREADS - 1)
        {
            end = num_words; // Ensure the last thread processes until the end
        }

        for (int i = start; i < end; i++)
        {
            for (int j = 0; j < strlen(text[i]); j++)
            {
                char c = text[i][j];
                for (int k = 0; k < NUM_VOWELS; k++)
                {
                    if (c == vowels[k])
                    {
                        local_counts[k]++;
                    }
                }
            }
        }

#pragma omp critical
        {
            for (int k = 0; k < NUM_VOWELS; k++)
            {
                counts[k] += local_counts[k];
            }
        }
    }

    printf("Vowel counts:\n");
    for (int k = 0; k < NUM_VOWELS; k++)
    {
        printf("%c: %d\n", vowels[k], counts[k]);
    }

    return 0;
}
