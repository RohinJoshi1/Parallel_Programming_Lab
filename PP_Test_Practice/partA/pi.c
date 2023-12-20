#include<stdio.h>

#define TERMS 1000
int main() {
    double sum = 0.0;

    #pragma omp parallel for reduction(+:sum)
    for (int k = 0; k < TERMS; ++k) {
        double term = (k % 2 == 0 ? 1.0 : -1.0) / (2.0 * k + 1.0);
        sum += term;
    }

    double pi = 4.0 * sum;

    printf("Estimate of pi using %d terms: %.15f\n", TERMS, pi);

    return 0;
}
