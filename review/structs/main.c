#include <stdio.h>

typedef struct point
{
    int x; 
    int y;
    int arr[200];
} point;

// Structures are called by value (even with an array)
// All the content is being copied to this function
void changeMe(point p)
{
    // Use dot because it's a structure not a pointer dumbass
    p.x = 10;
    p.y = 20;
}
// Function will not change the value of whatever value is passed because we are passing a value not an address.

void changeMev2(point *p)
{
    p->x = 10;
    p->y = 20;
}

point changeMev3(point p)
{
    p.x = 10;
    p.y = 20;

    return p;
}

// how to take an array in a function?
// if you use (int *a), it's the same thing for the code
void changeArray(int a[], int size)
{
    // can this func take int array? Yes, same thing for (*a)
    // This function doesn't know size, so pass size every time
    int i;
    for(i = 0; i < size; i++)
    {
        // a -> Address | a[i] -> Array Element
        a[i] = 10;
    }
    // No need to return array, they are always called by reference.
}

// Question: If you have function fun(myarr[0]) in this case you are calling by value because myarr[0] is a value

int main(void){
    int myarr[] = {20, 30, 40, 50};

    changeArray(myarr, 4);
    
    // The number "4" needs to be #define before, because it's confusing in the code
    for(int i = 0; i < 4; i++){
        printf("%d ", myarr[i]); // array name is the address of the first element of the array
    }

    point p1;
    p1.x = 100;
    p1.y = 200;

    p1 = changeMev3(p1);
    printf("%d %d\n", p1.x, p1.y);

    return 0;
}