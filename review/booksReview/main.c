#include <stdio.h>
#include <string.h>
#define SIZE 2

// creating type for storing properties of books
typedef struct Books{
    char title[50];
    char author[50];
    float price;
    int pageNum;
}Books;

int main(void){
    // creating drawer for Books
    Books book[SIZE];
    char x;

    // Looping through number of books
    for(int i = 0; i < SIZE; i++)
    {
        printf("Title of Book #%d: ", i+1);
        scanf("%[^\n]s", book[i].title);
        // clearing up the \n from last input
        while((x=getchar() != '\n') && x != EOF);
        printf("Author of Book #%d: ", i+1);
        scanf("%[^\n]s", book[i].author);
        printf("Price of Book #%d: ", i+1);
        scanf("%f", &book[i].price);
        printf("Number of pages of Book #%d: ", i+1);
        scanf("%d", &book[i].pageNum);
        // clearing up \n from last input
        while((x=getchar() != '\n') && x != EOF);
    }

    for(int i = 0; i < SIZE; i++)
    {
        printf("\n=======================\nInfo on Book #%d\nTitle: %s\nAuthor: %s\nPrice: %f\nPages: %d\n===========================\n", i+1, book[i].title, book[i].author, book[i].price, book[i].pageNum);
    }
    
    // asking user for input
    char ans = 'y';
    printf("Do you want to search for a specific book? (y/n): ");
    while(ans != 'n')
    {
        scanf("%c", &ans);
        
        char key[50];
        // asking for key
        printf("Who is the author? ");
        scanf("%[^\n]s", key);
        
        // loop through books to find match with key
        for(int i = 0; i < SIZE; i++)
        {
            if(strcmp(book[i].author, key) == 0)
            {
                printf("\n=======================\nInfo on Book #%d\nTitle: %s\nAuthor: %s\nPrice: %f\nPages: %d\n===========================\n", i+1, book[i].title, book[i].author, book[i].price, book[i].pageNum);
            }
        }
    }
    
    return 0;
}

