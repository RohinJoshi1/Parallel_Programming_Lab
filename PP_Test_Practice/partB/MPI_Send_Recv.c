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
    char *buffer;
    int msg_size =64;
    // while(msg_size < 100000){
    //     msg_size *=2;
    //     buffer = (char*)malloc(msg_size*sizeof(char));
    //     if(rank==0){
    //     MPI_Send(buffer, msg_size, MPI_CHAR, 1, 0,MPI_COMM_WORLD);
    //     printf("0: MEssage sent\n");
    //     fflush(stdout);
    //     MPI_Recv(buffer, msg_size, MPI_CHAR, 1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //     }
    //     else if(rank ==1){
    //         MPI_Recv(buffer,msg_size,MPI_CHAR, 0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //         printf("1:Received ");
    //         MPI_Send(buffer, msg_size, MPI_CHAR, 0, 0,MPI_COMM_WORLD);
    //         printf("1: sent");
    //         fflush(stdout);
    //     }
    //     free(buffer);
    // }
    while (msg_size < 100000)
    {
        msg_size *=2;
        buffer = (char*)malloc(msg_size*sizeof(char));
        if(rank==0){
            //Do an isend here
            MPI_Request req = MPI_REQUEST_NULL;
            MPI_Isend(buffer,msg_size,MPI_CHAR, 1, 0 ,MPI_COMM_WORLD, &req);
            fflush(stdout);
            MPI_Recv(buffer, msg_size, MPI_CHAR, 1,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }else if(rank==1){
            MPI_Recv(buffer,msg_size,MPI_CHAR, 0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("1:Received ");
            MPI_Send(buffer, msg_size, MPI_CHAR, 0, 0,MPI_COMM_WORLD);
            printf("1: sent");
            fflush(stdout);
        }
        free(buffer);
    }
    
    MPI_Finalize();
    return 0;
}
