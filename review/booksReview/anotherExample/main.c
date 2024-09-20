#include <stdio.h>
#include <string.h>
#define SIZE 3

typedef struct Date
{
    int day;
    int month;
    int year;
}Date;

struct Author{
    char authorName[50];
    char authorLanguage[50];
    Date dob; // Date was typedef so no struct
};

// This structure has the property author, which is type Author, this means that it also possess the properties of the author struct within that variable, AND the Struct author has the variable Dob which is type Date, so there's more properties in there.
typedef struct Book{
    char title[50];
    struct Author author; // Author is a structure variable
    float price;
    int pages;
}Book;

int main(void)
{
    Date d;
    d.year = 2020;
    d.month = 7;
    d.day = 1;

    Book b1;
    
    // Assign the word "cbook" to b1
    strcpy(b1.title, "cbook");

    // Assign Date d to the author
    b1.author.dob = d;

    // Change author's date of birth to 1995
    b1.author.dob.year = 1995;

    return 0;
}