#include <stdio.h>

typedef struct Date
{
    int day;
    int month;
    int year;
}Date;

int main(void)
{
    // Created box for storing struct properties
    struct Date d1; 
    d1.year = 2021;
    scanf("%d", &d1.month); // Taking input for struct

    // You want to have 100 dates:
    Date d[100]; // Created 100 boxes to store different dates

    // Use this to access a particular item in the array
    //* d[i].day

    return 0;
}