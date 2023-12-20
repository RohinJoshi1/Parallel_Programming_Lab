#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#define SIZE 20 
int main(int argc, char *argv[])
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    // int root = 0;
    // int buffer[4];
    // int local_val;
    // int local_send_val = rank*100;
    // if(rank == 0){
    //     for(int i=0;i<4;i++){
    //         buffer[i]=i*100;
    //     }
    // }
    // MPI_Scatter(buffer, 1, MPI_INT, &local_val, 1, MPI_INT, root, MPI_COMM_WORLD);
    // printf("RANK %d received value %d",rank, local_val);

    // if(rank == 0){
    //     int buf[4];
    //     MPI_Gather(&local_send_val, 1, MPI_INT,&buf, 1, MPI_INT, 0,MPI_COMM_WORLD);
    //     for(int i=0;i<4;i++){
    //         printf("\n%d",buf[i]);
    //     }
    // }else{
    //     MPI_Gather(&local_send_val, 1, MPI_INT,NULL, 1, MPI_INT, root,MPI_COMM_WORLD);
    // }
    int root = 0;
    int local_sum =0;
    int local_size =  SIZE / size;
    int local_arr[local_size];
    int sum[size];
    //Scatter Gather 
    //0. Create arr 
    int arr[SIZE];
    if(rank == root){
        for(int i=0;i<SIZE;i++){
            arr[i] = i+1;
        }
    }
    //1. Scatter local_size to subroutines
    MPI_Scatter(arr,local_size, MPI_INT , local_arr, local_size, MPI_INT, root, MPI_COMM_WORLD);

    //2 . Find the local sum
    for(int i=0;i<local_size;i++){
        local_sum+=local_arr[i];
    }

    //3.Gather 
    MPI_Gather(&local_sum, 1, MPI_INT, sum,1, MPI_INT, root, MPI_COMM_WORLD);
    if(rank == root){
        int _sum = 0;
        for(int i=0;i<size;i++){
            _sum+=sum[i];
        }
        printf("\n Computed sum = %d",_sum);
    }

    

    MPI_Finalize();

}
