#include <stdio.h>
#include <omp.h>

int main() {
    const int n = 10;
    int sequence[n];
    
    // Set the first two elements manually
    sequence[0] = 1;
    sequence[1] = 3;

    #pragma omp parallel for
    for (int i = 2; i < n; i++) {
        // Each element is the sum of the previous two elements
        sequence[i] = sequence[i - 1] + sequence[i - 2];
    }

    // Print the sequence
    printf("Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}
