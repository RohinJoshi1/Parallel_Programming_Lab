#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<time.h>
#include<assert.h>

float* create_rand_arr(int n){
    float *rand_arr = (float *)malloc(n*sizeof(float));
    assert(rand_arr!=NULL);
    for(int i=0;i<n;i++){
        rand_arr[i] = (rand() / (float)RAND_MAX);
    }
    return rand_arr;
}

float compute_avg(float *arr,int n){
    float sum = 0.0f;
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum/n;
}

int main(int argc, char *argv[])
{
    //Scatter Gather
    int num_el_per_proc = atoi(argv[1]);
    MPI_Init(NULL,NULL);
    int world_rank;
    int world_size;
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    float *randnums = NULL;
    if(world_rank==0){
        randnums = create_rand_arr(num_el_per_proc*world_size);
    }
    //Now that we have an array, we need to split it into smaller arrays to be distributed
    float *subarr = (float *)malloc(num_el_per_proc * sizeof(float));
    assert(subarr!=NULL);
    /*
    MPI_Scatter(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
    */

   //SCATTER
   MPI_Scatter(randnums,num_el_per_proc,MPI_FLOAT,subarr,num_el_per_proc,MPI_FLOAT,0,MPI_COMM_WORLD);

   //Compute the average for every sub arr 
   float sub_avg = compute_avg(subarr, num_el_per_proc);

   //GATHER
   /*
   MPI_Gather(
    void* send_data,
    int send_count,
    MPI_Datatype send_datatype,
    void* recv_data,
    int recv_count,
    MPI_Datatype recv_datatype,
    int root,
    MPI_Comm communicator)
   */

    float *sub_avgs = NULL;
    if(world_rank == 0){
        sub_avgs = (float *)malloc(sizeof(float)*world_size);
        assert(sub_avgs);
    }
    MPI_Gather(&sub_avg,1,MPI_FLOAT,sub_avgs,1,MPI_FLOAT,0,MPI_COMM_WORLD);

    if(world_rank == 0){
        float avg = compute_avg(sub_avgs, world_size);
        printf("Average  = %f\n",avg);
        float og_avg= compute_avg(randnums,world_size*num_el_per_proc);
        printf("Actual avg = %f\n",og_avg);
    }

    if (world_rank == 0) {
    free(randnums);
    free(sub_avgs);
  }
  free(subarr);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
    return 0;
}
