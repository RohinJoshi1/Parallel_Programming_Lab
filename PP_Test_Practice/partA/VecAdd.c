#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define SIZE 100
void addVecSeq(int *a, int *b, int *c){
    for(int i=0;i<SIZE;i++){
        c[i] = a[i]+b[i];
    }
}
void addVecPar(int *a, int *b, int *c){
    #pragma omp parallel for
    for(int i=0;i<SIZE;i++){
        c[i] = a[i]+b[i];
    }
}
int main(int argc, char const *argv[])
{
    int *a, *b,*c;
    a = (int*)malloc(SIZE*(sizeof(int)));
    b = (int*)malloc(SIZE*(sizeof(int)));
    c = (int*)malloc(SIZE*(sizeof(int)));

    for(int i=0;i<SIZE;i++){
        a[i] = rand()%100;
        b[i] = rand()%100;
        c[i] = rand()%100;
    }
    printf("Serial \n");
    double start = clock();
    addVecSeq(a,b,c);
    double stop = clock();
    printf("\nTime = %lf",stop-start);


    printf("\nParallel \n");
    start = clock();
    addVecPar(a,b,c);
    stop = clock();
    printf("\nTime = %lf",stop-start);

    free(a);
    free(b);
    free(c);
    return 0;
}
