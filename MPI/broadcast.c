/*
This code covers the use of broadcast and barrier 
*/

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<assert.h>

void bcast_iter(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm Communicator){
    int world_rank;
    int size;
    MPI_Comm_rank(Communicator,&world_rank);
    MPI_Comm_size(Communicator, &size);
    if(world_rank==root){
        //Broadcast 
        for(int i=0;i<size;i++){
            if(i!=world_rank){
                MPI_Send(data,count, datatype, i,0,Communicator);
            }
        }
    }else{
        MPI_Recv(data,count, datatype, root,0,Communicator,MPI_STATUS_IGNORE);
    }
}
// We will first run the in built mpi bcast cmd
int main(int argc, char  *argv[])
{
    int num_elements = atoi(argv[1]);
    int num_trials = atoi(argv[2]);
    MPI_Init(NULL,NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    double my_bcast_time= 0.0;
    double mpi_bcast_time = 0.0;
    int* data = (int*)malloc(sizeof(int)*num_elements);
    assert(data!=NULL);
    for(int i=0;i<num_trials;i++){
        MPI_Barrier(MPI_COMM_WORLD);
        my_bcast_time -= MPI_Wtime();
        bcast_iter(data,num_elements,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        my_bcast_time += MPI_Wtime();
    }
     for(int i=0;i<num_trials;i++){
        MPI_Barrier(MPI_COMM_WORLD);
        mpi_bcast_time -= MPI_Wtime();
        MPI_Bcast(data,num_elements,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        mpi_bcast_time += MPI_Wtime();
    }
     if (rank == 0) {
    printf("Data size = %d, Trials = %d\n", num_elements * (int)sizeof(int),
           num_trials);
    printf("Avg my_bcast time = %lf\n", my_bcast_time / num_trials);
    printf("Avg MPI_Bcast time = %lf\n", mpi_bcast_time / num_trials);
  }

free(data);
MPI_Finalize();

    return 0;
}
 