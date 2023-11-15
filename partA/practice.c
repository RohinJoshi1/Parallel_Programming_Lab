//fib

#include<stdio.h>

fib(int n){
    int arr[n];;
    arr[0]=0;
    arr[1]=1;
    #pragma omp parallel for schedule(dynamic)
    for(int i=2;i<=n;i++){
        arr[i] = arr[i-1]+arr[i-2];
    }
}
void merge(int a[],int l,int m, int r){
    int n1 = m-l+1;
    int n2 = r-m;
    int ll[n1];
    int rr[n2];
    for(int i=0;i<n1;i++){
        ll[i] = a[l+i];
    }
    for(int i=0;i<n2;i++){
        rr[i] = a[m+1+i];
    }
    int i=0;
    int j=0;
    int k=l;
    while(i<n1 && j < n2){
        if(ll[i]<rr[j]){
            a[k]=ll[i++];
        }else{
            a[k] = rr[i++];
        }
        k++;
    }
    while(i<n1){
        ll[i++] = a[k++];
    }
    while(j<n2){
        rr[j++] = a[k++];
    }
}
void mergesort(int a[],int l, int r){
    if(l < r){
        int m = l + (r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(a,l,m);
            #pragma omp section
            mergesort(a,m+1,r);
        }
       
        merge(a,l,m,r);
    }
}
void thread_Id(){
    int num_threads, num_iterations;
    printf("Enter the number of iterations: ");
    scanf("%d", &num_iterations);

    
    #pragma omp parallel 
    {
        num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        #pragma omp for 
        for(int i=0;i<num_iterations;i++){
            if(i%num_threads==thread_id){
                int start = i;
                int stop = i+1;
                printf("Thread %d : Iterations %d -- %d\n", thread_id, start, stop);
            }
        }

    }
}