#include <stdio.h>
#include <string.h>
#include <omp.h>

#define NUM_WORDS 100000
#define NUM_VOWELS 10
#define NUM_THREADS 4

char text[NUM_WORDS][100]; // assuming each word has at most 100 characters

int main()
{
    int counts[NUM_VOWELS] = {0}; // counts for vowels a, A, e, E, i, I, o, O, u, U
    char vowels[NUM_VOWELS] = {'a', 'A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

    // Initialize text array with dummy data for demonstration
    for (int i = 0; i < NUM_WORDS; i++)
    {
        strcpy(text[i], "This is a sample text with vowels AEIOU aeiou");
    }

#pragma omp parallel for reduction(+ : counts[ : NUM_VOWELS])
    for (int i = 0; i < NUM_WORDS; i++)
    {
        for (int j = 0; j < strlen(text[i]); j++)
        {
            char c = text[i][j];
            for (int k = 0; k < NUM_VOWELS; k++)
            {
                if (c == vowels[k])
                {
                    counts[k]++;
                }
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
