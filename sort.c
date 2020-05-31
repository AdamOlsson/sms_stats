#include "sort.h"

void mergeSort(int values[], char * keys[], int l, int r){
    if(l < r){
        int m = l + (r-l)/2;
        mergeSort(values, keys, l, m);
        mergeSort(values, keys, m+1, r);

        merge(values, keys, l, m, r);
    }
}
void merge(int values[], char* keys[], int l, int m, int r){ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    int L[n1], R[n2];
    char *LC[n1], *RC[n2];
  
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++){
        L[i] = values[l + i];
        LC[i] = keys[l + i];
    } 
    for (j = 0; j < n2; j++){
        R[j] = values[m + 1 + j]; 
        RC[j] = keys[m + 1 + j];
    }
  
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2){ 
        if (L[i] <= R[j]){ 
            values[k] = L[i];
            keys[k] = LC[i];
            i++; 
        }else{ 
            values[k] = R[j]; 
            keys[k] = RC[j];
            j++; 
        } 
        k++; 
    } 
  
    /* Copy the remaining elements of L[], if there 
       are any */
    while (i < n1){ 
        values[k] = L[i]; 
        keys[k] = LC[i];
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2){ 
        values[k] = R[j]; 
        keys[k] = RC[j];
        j++; 
        k++; 
    } 
} 