#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    char sender_msg[100];
    char receiver_msg[100];
    double start_time, end_time;
    if(rank==0){
        sprintf(sender_msg, "FROM 0");
        start_time = MPI_Wtime();
        MPI_Sendrecv(sender_msg, strlen(sender_msg)+1, MPI_CHAR,1,0,receiver_msg, 100,MPI_CHAR, 1, 0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        end_time = MPI_Wtime();
        printf("\n0: Received %s",receiver_msg);
        fflush(stdout);
    }else if(rank==1){
        sprintf(receiver_msg, "FROM 1");
        start_time = MPI_Wtime();
        MPI_Sendrecv(receiver_msg, strlen(receiver_msg)+1, MPI_CHAR, 0,0,sender_msg, 100, MPI_CHAR, 0,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        end_time = MPI_Wtime();
        printf("\n1: Received %s",sender_msg);
        fflush(stdout);

        }
    double bw = (double)((strlen(sender_msg)+1)*sizeof(char)*size) / (end_time-start_time);
    if(rank ==0 ){
        printf("\n BW = %lf B/s",bw);
    }
    MPI_Finalize();
    return 0;
}
