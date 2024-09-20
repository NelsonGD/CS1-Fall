/*
Function that will DMA an int array.

The array factory recieves the size of the array. 
    - This is so it knows how much memory it will need.

Remember: malloc gives the starting address of array.
    - Basically gives you the blocks where you are going to store the addresss. Then you need to store that address somewhere
*/

#include <stdio.h>
#include <stdlib.h>

int* arrayFactory(int n)
{
    // creating empty array
    int* m = (int*)malloc(n*sizeof(int));
    for(int i = 0; i < n; i++){
        // Remember than m[i] is an integer box so you are going directly to a value
        m[i] = 1 + rand()%100;
    }

    // to return the array all you need to give them is the variable that mangaes the array, which is m.
    return m;
}
// After function is done running m is gone. This is because it's statically allocated.

int main(void){

    int size;
    printf("How many int do you want? ");
    scanf("%d", &size);
    
    // You are giving it to an integer pointer because the function is return the starting address of an array.
    int *p = arrayFactory(size);

    for(int i = 0; i < size; i++){
        printf("%d ", p[i]++);
    }

    //p = arrayFactory(10); //! This line creates a memory leak because now you can't go back to the original array.

    // if you don't need orinigal array
    free(p); // Since you onlu used one malloc, then you only need one free.

    // Now you can use p again to point to another array.
    // If you do need the original still, then just store the new array using another int pointer.
    int *p1 = arrayFactory(10);
    printf("\n");
    for(int = 0; i < 10; i++){
        
    }

    return 0;
}