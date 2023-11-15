#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
int main(int argc, char *argv[])
{
    MPI_Init(&argc,&argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);

    char rank_0_sendbuf[100];
    char rank_1_sendbuf[100];

    if(world_rank == 0){
        sprintf(rank_0_sendbuf ,"Hello world from %d",world_rank);
             //params : data, count, datatype, dest, tag, communicator
        MPI_Recv(rank_1_sendbuf,100,MPI_CHAR,1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(rank_0_sendbuf,strlen(rank_0_sendbuf)+1,MPI_CHAR,1,0,MPI_COMM_WORLD);
       
        printf("RANK 0:received buffer with content %s",rank_1_sendbuf);
    }
    else if(world_rank ==1){
        sprintf(rank_1_sendbuf ,"Hello world from %d",world_rank);
             //params : data, count, datatype, dest, tag, communicator
        MPI_Recv(rank_0_sendbuf,100,MPI_CHAR,0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Send(rank_1_sendbuf,strlen(rank_1_sendbuf)+1,MPI_CHAR,0,0,MPI_COMM_WORLD);
       
        printf("RANK 1:received buffer with content %s",rank_0_sendbuf);
    }

    MPI_Finalize();
    return 0;
}
