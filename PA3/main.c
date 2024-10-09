#include <stdio.h>
#define MAXGARAGES 10

void printPermutArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void mypermute(int arr[], int used[], int k, int n)
{
    // If k reaches length then print array.
    if(k == n)
        printPermutArray(arr, n);
    for(int i = 0; i < n; i++)
    {
        if(!used[i]) // if i was not used
        {
            used[i] = 1; // mark it used.
            arr[k] = i; // transwer i to the perm array at kth position
            mypermute(arr, used, k+1, n); // increases k nd grow further
            used[i] = 0; // unmark i for next process
        }
    }
}

int main(void)
{
    int perm[MAXGARAGES] = {0}; // To build and store the permutation
    int used[MAXGARAGES] = {0}; // tracking which index/object is used
    mypermute(perm, used, 0, MAXGARAGES);

    printf("Hello World\n");
    return 0;
}