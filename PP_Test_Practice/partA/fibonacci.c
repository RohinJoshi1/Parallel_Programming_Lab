#include<stdio.h>

int main(int argc, char const *argv[])
{
    int n=10;
    long long fib[n];
    int i=0;
    fib[0]=0;
    fib[1] =1;
    #pragma omp parallel for schedule(dynamic)
    for(int i=2;i<n;i++){
        fib[i] = fib[i-1]+fib[i-2];
    }
    for(int i=0;i<n;i++){
        printf("\t%lld",fib[i]);
    }
    return 0;
}
