#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void addVectorsSequential(int a[], int b[], int c[],int n){
    for(int i=0;i<n;i++){
        c[i] = a[i]+b[i];
    }
}
void addVectorsParallel(int a[], int b[], int c[],int n){
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        c[i] = a[i]+b[i];
    }
}

int main(int argc, char const *argv[])
{
    int n;
    printf("Enter n\n");
    scanf("%d",&n);
    int a[n],b[n];
    for(int i=0;i<n;i++){
        a[i] = rand()%1000;
        b[i] = rand()%1000;
    }
    int c[n];
    printf("Serial\n");
    double start = clock();
    addVectorsSequential(a,b,c,n);
    double stop = clock();
    printf("\n%lf",(double)(stop-start));
    printf("parallel\n");
    start = clock();
    addVectorsParallel(a,b,c,n);
    stop = clock();
    printf("\n%lf",(double)(stop-start));

    for(int i=0;i<n;i++){
        printf("\n%d",c[i]);
    }




    return 0;
}

