#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

/**
 * Program to find Prime numbers using parallel for
*/

bool isPrime(int n){
    if(n < 2)return false;
    for(int i=2;i*i < n;i++){
        if(n%i==0)return false;
    }
    return true;
}
int main(int argc, char const *argv[])
{
    int n;
    printf("\nEnter n\t");
    scanf("%d",&n);
    //Serial execution 
    printf("Sequential\n");
    double start = clock();
    for(int i=2;i<=n;i++){
        if(isPrime(i)){
            printf("\n%d",i);
        }
    }
    double stop = clock();
    double dff= stop -start;
    printf("\nSERIAL %lf",dff);

    //PARALLEL

     printf("Parallel\n");
    start = clock();
    #pragma omp parallel for
    for(int i=2;i<=n;i++){
        if(isPrime(i)){
            printf("\n%d",i);
        }
    }
    stop = clock();
    dff= stop -start;
    printf("\nParallel %lf",dff);


    return 0;
}

