#include <stdio.h>

/* Create a function that takes in a list and 
after each even number it will mark it by 
adding a -1 next to it in the list

1*/

struct node
{
    int data;
    struct node* next;
}node;

int main(void)
{   


    return 0;
}

void markEven(struct node* head)
{
    // Empty List Case
    if(head == NULL)
        return;

    struct node* w  = head; // walker
    while(w) // while walker is not equal to null
    {
        if(w->data % 2 == 0) // check if even
        {
            struct node* new = malloc(sizeof(struct node));
            new -> data = -1; // value to plug in
            new -> next = NULL;
            new -> next = w -> next;
            w -> next = new;
            w = w -> next -> next;
        }else{
            w = w -> next;
        }
    }
}