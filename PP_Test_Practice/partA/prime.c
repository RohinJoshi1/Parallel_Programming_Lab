#include<stdio.h>
#include<time.h>
#include<stdbool.h>

bool isPrime(int n){
    if(n < 2) return false;
    for(int i=2;i*i<n;i++){
        if(n%i==0)return false;
    }
    return true;
}


int main(int argc, char const *argv[])
{
    printf("Enter no.");
    int  n;
    scanf("%d",&n);
    printf("\nSequential\n");
    double start= clock();
    for(int i=2;i<=n;i++){
        if(isPrime(i)){
            printf("\t%d", i);
        }
    }
    double stop = clock();
    printf("\n S time = %lf",stop-start);


    printf("PARALLEL\n");
    start= clock();
    #pragma omp parallel for
    for(int i=2;i<=n;i++){
        if(isPrime(i)){
            printf("\t%d", i);
        }
    }
    stop = clock();
    printf("\n P time = %lf",stop-start);
    
    return 0;
}
