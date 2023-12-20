#include<stdio.h>
#include<stdlib.h>

/**
 *  Write an OpenMP program that divides the Iterations into chunks containing 2 iterations, 
 * respectively (OMP_SCHEDULE=static,2). Its input should be the number of iterations, 
 * and its output should be which iterations of a parallelized for loop are executed by which thread. 
 * For example, if there are two threads and four iterations, the output might be the following:
    
    a.	Thread 0 : Iterations 0 −− 1
    
    b.	Thread 1 : Iterations 2 −− 3

*/
int main(int argc, char const *argv[])
{
    int iter;
    printf("Enter no.of iterations\n");
    scanf("%d",&iter);
    printf("enter no.of threads\n");
    int num_threads;   
    scanf("%d",&num_threads);
    if(num_threads > 4){
        printf("NOPE");
        return 0;
    }
    omp_set_num_threads(num_threads);
    #pragma omp parallel for schedule(static,2)
    for(int i=0;i<iter;i++){
        printf("Thread %d: Iterations %d -- %d\n",omp_get_thread_num(), i,i+1);
    }

    return 0;
}
