#include<stdio.h>
/*
Write a program to
calculate the sum of first 100 Numbers. (Using critical directive)
*/
int main(){
    int total,partial;
    #pragma omp parallel private(partial) shared(total)
    {
        total=0;
        partial=0;
        #pragma omp for 
        for(int i=0;i<1000;i++){
            partial+=i;
        }
        #pragma omp critical 
        {
            total+=partial;
        }
    }
    printf("\n%d is the total sum",total);
}
