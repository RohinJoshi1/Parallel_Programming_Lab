#include<stdio.h>
#include<time.h>
/**
 * 2.Estimate the value of pi using:
 * 4*SUM((-1)^k/(2k+1))

Parallelize the code by 
removing loop carried dependency 
and record both serial and parallel execution times.
*/
int main(int argc, char const *argv[])
{
    int n = 100000;
    double pi =0;
    int i;
    double start = clock();
    #pragma omp parallel for private(i,pi)
    for(i=0;i<n;i++){
        double num = i%2==0 ? 1 : -1;
        pi += (num/(2*i+1));        
    }
    pi*=4;
    double stop = clock();
    
    double dff  = stop -start;
    printf("\n Time is %lf",dff);
    printf("\n%lf",pi);

    return 0;
}

