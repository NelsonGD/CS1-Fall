#include <stdio.h>

struct node
{
    int data;
    struct node* next, prev;
}node;

struct queue
{
    int size;
    struct node* head;
    struct node* tail;
}queue;

int main(void)
{

    
    return 0;
}

int deQueue(struct queue* thisQ)
{
    if(thisQ == NULL) // if empty
        return 0;

    if(thisQ -> size == 0) // same thing as checking if empty
        return 0;
    
    if(thisQ -> head == thisQ -> tail) // if one itme in queue
    {
        int temp = thisQ -> head -> data;
        free(thisQ -> head);
        thisQ -> tail = NULL;
        thisQ -> size--;
        return temp;
    }
}   