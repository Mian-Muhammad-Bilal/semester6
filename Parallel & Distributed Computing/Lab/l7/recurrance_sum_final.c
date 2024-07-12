#include <stdio.h>
#include <omp.h>

int main() {
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

    // Sequential computation of sequence terms
    for (int i = 1; i < n; i++) {
        // Compute the value of the sequence term
        sequence[i] = sequence[i - 1] + 3;
    }

    // Parallel computation of updating the sequence array
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        // No need to recompute the first term
        if (i == 0)
            continue;
        
        // Compute the value of the sequence term
        sequence[i] = sequence[i - 1] + 3;
    }

    // Print the sequence
    printf("Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
