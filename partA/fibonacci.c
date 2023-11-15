#include<stdio.h>
// #include "/opt/homebrew/Cellar/libomp/17.0.1/include/omp.h"
/**
 * 4.Write a program to calculate n Fibonacci numbers using Parallel Directive. 
 * Demonstrate elimination of the race condition using Schedule directive.
*/
int main(int argc, char const *argv[])
{
    int n;
    printf("enter n");
    scanf("%d",&n);
    long long fib[n];
    int i;
    fib[0] = 0;
    fib[1] = 1;
    #pragma omp parallel 
    {
        #pragma omp for schedule(dynamic)
        for (i = 2; i < n; i++)
        {
            fib[i] = fib[i-1]+fib[i-2];
        }
        
    }
    printf("Fibonacci Sequence:\n");
    for (i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");
    return 0;
}


