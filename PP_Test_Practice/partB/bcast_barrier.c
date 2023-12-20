#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);
    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD , &rank);
    MPI_Comm_size(MPI_COMM_WORLD , &size);
    //Broadcast the message to everyone 
    int message;
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == 0){
        printf("Broadcasting to the world!\n");
        message = 1235;
    }
    MPI_Bcast(&message,1,MPI_INT,0,MPI_COMM_WORLD);
    printf("\nRank %d received bcast message %d\n",rank,message);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}