#include <stdio.h>
#include <string.h>

typedef struct Book{
    char title[50];
    char author[50];
    int pages;
    float price;
}Book;

// Same as:
//void printmeV1(char *t, char *a, int pages, float price)
void printmeV1(char t[], char a[], int pages, float price)
{
    printf("\n%s %s %d %.2f\n", t, a, pages, price);
}
// This function has no idea about the structure BUT it can take information in the main function
// The problem here is that you will have bigger structs and passing each thing is horrible SOOOOO...

// take entire structure copy
void printmeV2(struct Book b) // Structures are passed by VALUE
{
    printf("\n%s %s %d %.2f\n", b.title, b.author, b.pages, b.price);

    // Trying to change the price
    b.price = 2000;
}
// Wont be able to change values because all you are doing is copying and pasting values into a function
// This method is very inefficient in many cases due to having bigger structures

void printmeV3(struct Book *b)
{
    printf("\n%s %s %d %.2f\n", b->title, b->author, b->pages, b->price);

    // Now we can change the value
    b->price = 2000;
}

int main(void){
    struct Book b1 = {"Java book", "Java author", 200, 50.5};

    printmeV1(b1.title, b1.author, b1.pages, b1.price);

    printmeV2(b1);
    printf("The price is now: %f\n", b1.price);

    printmeV3(&b1);
    printf("The price is now: %f\n", b1.price);

    printf("The size of the struct is %u\n", sizeof(b1));

    // How to copy all info form b1 to b2
    Book b2;
    b2 = b1; // It will copy your struct
    // Completely different entities (so different address), same content.ßßßßßßß

    return 0;
}