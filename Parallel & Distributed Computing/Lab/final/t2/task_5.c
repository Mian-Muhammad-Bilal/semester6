#include <stdio.h>
#include <omp.h>

int main()
{
    int n;
    printf("Enter the number of terms in the sequence: ");
    scanf("%d", &n);

    // Initialize array to store sequence
    int sequence[n + 1];
    sequence[0] = 1;

    int start_value;
    printf("Enter the starting value of the sequence: ");
    scanf("%d", &start_value);
    sequence[1] = start_value;

#pragma omp parallel for
    for (int i = 2; i <= n; i++)
    {
        sequence[i] = sequence[i - 1] + 3;
    }

    // Print the sequence
    printf("Sequence: ");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
