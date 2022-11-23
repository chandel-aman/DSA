#include <stdio.h>

//merging two subarrays L and M into the given array
void merge(int arr[], int p, int q, int r){
    int n1 = q - p+1;
    int n2 = r-q;
    int L[n1], M[n2];
    for(int i = 0; i<n1; i++){
        L[i] = arr[p+i];
    }
    for(int j = 0; j<n2; j++){
        M[j] = arr[q+1+j];
    }

    //maintain current index of subarray and main array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    //until we reach either end of L or M, pick laarger among elements L and M and place them in the correct position at A[p...r]
    while(i<n1 &&j<n2){
        if(L[i]<=M[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    //when we run out of elements in either L or M, pick up the remaining elements and put in A[p...r]
    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j<n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}

//divide the array into two sub arrays, sort them and merge them
void mergeSort(int arr[], int l, int r){
    if(l<r){
        //m is the point where the array is divided into two subarrays
        int m = l + (r-l)/2;
        mergeSort(arr, l , m);
        mergeSort(arr, m+1 , r);

        //merge the sorted subarrays
        merge(arr, l, m, r);
    }
}

//print the array
void printArray(int arr[], int size){
    for(int i = 0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

//main function
void main(){
    int ar[] = {6, 5, 12, 10, 9, 1};
    int size = sizeof(ar)/sizeof(ar[0]);
    mergeSort(ar, 0, size-1);
    printf("Sorted Array\n");
    printArray(ar, size);
}
