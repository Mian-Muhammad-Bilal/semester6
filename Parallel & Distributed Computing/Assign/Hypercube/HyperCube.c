#include <stdio.h>
#include <omp.h>
#include <math.h>

#define P 16 // no. of processors

void print_values(int values[], const char *message)
{
    printf("%s\n", message);
    for (int i = 0; i < P; i++)
    {
        printf("Processor %d: %d\n", i, values[i]);
    }
}

void perform_hypercube_steps(int values[])
{
    int num_itra = (int)log2(P); // Calculate log2(N), log2(16) = 4
    for (int itration = 0; itration < num_itra; itration++)
    {
#pragma omp parallel
        {
            int adjacentNode;
            int local_values[P];

#pragma omp for
            for (int i = 0; i < P; i++)
            {
                local_values[i] = values[i];
            }

#pragma omp for
            for (int i = 0; i < P; i++)
            {
                adjacentNode = i ^ (1 << itration);
                local_values[i] += values[adjacentNode];
            }

#pragma omp for
            for (int i = 0; i < P; i++)
            {
                values[i] = local_values[i];
            }
        }

        char message[50];
        snprintf(message, sizeof(message), "\nValues after itration %d:", itration + 1);
        print_values(values, message);
    }
}

int main()
{
    int values[P] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    print_values(values, "Initial values:");

    perform_hypercube_steps(values);

    print_values(values, "\nFinal values:");

    return 0;
}
