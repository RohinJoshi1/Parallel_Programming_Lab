#include<stdio.h>
#include<omp.h>

/**
 * 3.Write an OpenMP program that divides 
 * the Iterations into chunks containing 2 iterations, 
 * respectively (OMP_SCHEDULE=static,2). Its input should 
 * be the number of iterations, and its output should be which 
 * iterations of a parallelized for loop are executed by which thread. 
 * For example, if there are two threads and four iterations, 
 * the output might be the following:
a.Thread 0 : Iterations 0 −− 1
b.Thread 1 : Iterations 2 −− 3
*/
int main() {
    int num_threads, num_iterations;
    printf("Enter the number of iterations: ");
    scanf("%d", &num_iterations);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        num_threads = omp_get_num_threads();
        
        #pragma omp for schedule(static, 2)
        for (int i = 0; i < num_iterations; i++) {
            if (i % num_threads == thread_id) {
                int start = i;
                int end = i + 1;
                printf("Thread %d : Iterations %d -- %d\n", thread_id, start, end);
            }
        }
    }

    return 0;
}
