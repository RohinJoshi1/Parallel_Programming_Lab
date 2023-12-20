#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void merge(int arr[] , int l, int m, int r){
    int ls = m -l +1;
    int rs = r-m;
    int left[ls];
    int right[rs];

    //Copy left and right 
    for(int i=0;i<ls;i++){
        left[i] = arr[l+i];
    }
    for(int j=0;j<rs;j++){
        right[j] = arr[m+1+j];
    }
    int i=0,j=0;
    int k =l;
    while(i< ls && j <rs){
        if(left[i]<=right[j]){
            arr[k] = left[i++];
        }else{
            arr[k] = right[j++];
        }
        k++;
    }
    while(i< ls ){
        arr[k++] = left[i++];
    }
    while( j < rs){
        arr[k++] = right[j++];
    }
}
void MergeSort(int arr[], int l , int r){
    if(l < r){
        int mid = l + (r-l)/2;
        MergeSort(arr, l, mid);
        MergeSort(arr, mid+1, r);
        merge(arr, l,mid,r);
    }
}
void PmergeSort(int arr[], int l , int r){
    if(l < r){
        int mid = l + (r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            MergeSort(arr, l, mid);

            #pragma omp section
            MergeSort(arr, mid+1, r);
        }
        merge(arr, l,mid,r);
    }
}
int main(int argc, char const *argv[])
{
    int n = 5;
    int arr[] = {5,4,3,2,1};
    int cp[] = {5,4,3,2,1};
    double start = clock();
    MergeSort(arr, 0,n-1);
    for(int i=0;i<n;i++){
        printf("\t%d",arr[i]);
    }
    printf("Time taken \n");
    printf("%lf",clock()-start);
    printf("\nPARALLEL\n");
    start = clock();
    PmergeSort(cp, 0,n-1);
    for(int i=0;i<n;i++){
        printf("\t%d",arr[i]);
    }
    printf("Time taken \n");
    printf("%lf",clock()-start);


    return 0;
}
