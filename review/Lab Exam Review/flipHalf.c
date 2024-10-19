#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    int data;
    struct node_s* next;
} node_t;

/* To solve this problem we need to find the
half point of the linked list. Then iterate to the 
tail of the list, make that node point to the head,
and then make the node at the midpoint point to null.*/
node_t* flipHalf(node_t * head, int n) {
    if(!head)
        return NULL;

    node_t* newMiddle = head;
    node_t* newEnding = head;
    
    for(int i = 0; i < (n/2)-1; i++) // starting at 0 so remember to substract 1
        newMiddle = newMiddle->next;

    while(newMiddle)
        newEnding = newEnding->next;

    newMiddle->next = head;
    head = newMiddle;
    newEnding->next = NULL;

    return head;
}

int main(void){


    return 0;
}