#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>


int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    int val = (rank+1);

    int sum, min,max, prod;
    int root = 0;
    MPI_Allreduce(&val, &sum,1, MPI_INT, MPI_SUM,  MPI_COMM_WORLD);
    MPI_Allreduce(&val, &max,1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
    MPI_Allreduce(&val, &min,1, MPI_INT, MPI_MIN,  MPI_COMM_WORLD);
    MPI_Allreduce(&val, &prod,1, MPI_INT, MPI_PROD,  MPI_COMM_WORLD);


    printf("sum %d\n min %d\n max %d\n prod %d\n",sum,min,max, prod);




    MPI_Finalize();
}