#include <stdio.h>
#include <stdlib.h>

//function to swap the elements
void swap(int * a, int * b){
    int temp = * a ;
    * a = * b;
    *b = temp;
}

//function to find the partition position
int partition(int ar[], int low, int high){
    //selecting the rightmost element as the pivot
    int pivot = ar[high];

    //pointer for greater element
    int i = (low - 1);

    //traverse each element of the array and compare it with the pivot
    for(int j = low; j<high; j++){
        if(ar[j] <= pivot){
            i++;
            swap(&ar[i], &ar[j]);
        }
    }
    swap(&ar[i+1], &ar[high]);
    return (i+1);
}


//quick sort
void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
  
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//function to display the array
void display(int ar[], int high){
    for(int i = 0; i<high; i++){
        printf("%d ", ar[i]);
    }
    printf("\n");
}

void main(){
    int ar[] = {4,2,1,0,3};
    quickSort(ar, 0, 4);
    display(ar, 5);
}
