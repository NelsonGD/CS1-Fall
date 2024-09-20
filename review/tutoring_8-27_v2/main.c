/*
Agenda:
DMA for structs 
realloc
difference betweeen calloc and malloc

? Write the following function that takes in an integer n, your function should:
* Allocate an array of size n.
* Prompt the uesre for n numbers (to fill the array)
* return the array
*/

#include <stdio.h>
#include <stdlib.h>

int* createArray(int n){
    int* m = (int*)calloc(n, sizeof(int));

    return m;
}

int main(void){
    int size;
    printf("Size of array: ");
    scanf("%d", &size);

    int* arr = createArray(size);

    for(int i = 0; i < size; i++){
        printf("%d: %d\n", i+1, arr[i]);
    }

    return 0;
}