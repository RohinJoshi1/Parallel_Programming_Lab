#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int sumseq(int n){
    int sum =0;
    for(int i=1;i<=n;i++){
        sum+=i;
    }
    return sum;
}

int sumpar(int n){
    int sum =0;
    #pragma omp parallel for
    for(int i=1;i<=n;i++){
        #pragma omp critical
        sum+=i;
    }
    return sum;
}
int main(int argc, char const *argv[])
{
    int n = 100;
    printf(" Seq = %d",sumseq(n));
    printf("Par = %d",sumpar(n));
    return 0;
}

