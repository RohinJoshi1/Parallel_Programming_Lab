#include<stdio.h>
// #include "/opt/homebrew/Cellar/libomp/17.0.1/include/omp.h"
#include <stdlib.h>
#include <time.h>
#include<string.h>
/**
 * 1.Write a program to sort an array on n elements using both sequential
 *  and parallel merge sort(using Section). Record the difference 
 * in execution time.
*/

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;


    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential merge sort
void sequentialMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Parallel merge sort 
void parallelMergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    printf("Enter no. of elements");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i] = rand()%100;
    }
    int copy[n];
    for(int i=0;i<n;i++){
        copy[i]=arr[i];
    }
    double start = clock();
    sequentialMergeSort(arr,0,n);
    double stop = clock();
    double diff = (double)(stop-start);
    printf("\n time taken for sequential is %lf",diff);
    start = clock();
    parallelMergeSort(arr,0,n);
    stop = clock();
    diff = (double)(stop-start);
    printf("\n time taken for Parallel is %lf",diff);
}
