#include <stdio.h>

/*
This function is taking in the values of a and b, the problem is since 
it's passed by value it can't access the memory block (where the a and b are stored)
the function can't change the value of a and b in the main function, which is where
the values of a and b are, they are not in the swapUsPassByValue.
*/
void swapUsPassByValue(int x, int y){
    int temp;
    temp = x;
    x = y;
    y = temp;
}

/*
Ihis new function you just created 2 boxes, not two values.
This means you can now send the memory(box) location for a and b, 
so the function is accessing that memory space and changing it.
*/
void swapUsPassReference(int *x, int *y){
    int temp;
    temp = *x; // temp = a;
    *x = *y; // a = b;
    *y = temp;
}

void getxy(int *x, int *y){
    // The variables x and y already have the address 
    scanf("%d %d", x, y);
}

//? This is not valid, you can only put NULL into a POINTER
//! int n = NULL;

//? int n = 5, m = 10, *P1, *P2; 
//* P1 and P2 have garbage
// *P1 = 20; 
//! Technically valid in C, but it's copying 20 to garbage address (accessing illegal memory) = SEGMENTATION FAULT

// P2 = &P1
//! Not valid, P2 doesn't have enough power to point to another pointer
//* To fix change the definition of P2 -> *P2 (can't store another pointer) || **P2 (CAN store another pointer)
// Correct version: int *P1, **P2;   ->      P2 = &P1 

void makeNull(int *p){
    p = NULL;
}

int main(void){
    //? PASSING BY VALUE VS PASSING BY REFERENCE
    int a = 5, b = 10; 
    
    swapUsPassByValue(a , b);
    printf("%d %d\n", a, b);

    swapUsPassReference(&a, &b);
    printf("a = %d b = %d\n", a, b);

    int x, y;
    getxy(&x, &y);

    //? POINTER TO POINTER
    int t, *p1;
    p1 = &t;
    makeNull(p1);

    if(p1 == &x)
        printf("p1 is still &x\n");

    if(p1 == NULL)
        printf("p1 is NULL\n");

    return 0;
}


