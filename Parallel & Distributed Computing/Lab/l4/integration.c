#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x)
{
    return sin(x) * cos(x);
}

int main()
{
    int num_steps = 1000000;
    double step = M_PI / (double)num_steps;
    double sum_positive = 0.0;
    double sum_negative = 0.0;

#pragma omp parallel for reduction(+ : sum_positive, sum_negative)
    for (int i = 0; i < num_steps; i++)
    {
        double x = i * step;
        double partial_sum = f(x);
        if (partial_sum >= 0)
        {
            sum_positive += partial_sum;
        }
        else
        {
            sum_negative += partial_sum;
        }
    }

    double result = (sum_positive + sum_negative) * step;
    printf("Positive sum: %f\n", sum_positive * step);
    printf("Negative sum: %f\n", sum_negative * step);
    printf("Result: %f\n", result);

    return 0;
}
