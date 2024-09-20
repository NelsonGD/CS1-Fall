/*
Nelson Diaz
COP3502C
Program uses function that will print a list,
insert a value at the front of a list, reverse
the order of a list, and insert to a specified 
place in the list. Functions are called through
a while loop menu.
*/

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// this function takes an item and insert it in the linked list pointed by root.
node *insert_front(node *head, int item)
{
    // Create a new node and allocate memory for it
    node *new_node = malloc(sizeof(node));
    new_node->data = item;

    // If the list is empty (head is NULL), set the new node's next to NULL
    // Otherwise, set its next to the current head
    new_node->next = head;

    // Return the new node as the new head of the list
    return new_node;
}

/* Function takes the head of a list, copies the
content of the original list into a new list but
each node is pointing in reverse order. Returns
the head of the new linked list */
node *reverse(node *head)
{
    node *reversedL = NULL;
    node *walker = head;

    while (walker)
    {
        node *temp = walker;
        walker = walker->next;
        temp->next = reversedL;
        reversedL = temp;
    }

    return reversedL;
}

/* Function takes a pointer to a list, the value to
insert, and also the place where to insert the new value.
Goes through list until finds position right before the
insertion place, creates node with value, and linkes it
to walker and walker-next.*/
void insertToPlace(node *list, int val, int place)
{
    if (place <= 1)
    {
        printf("List is empty or place is not valid");
        return;
    }

    // Node for going through list.
    node *walker = list;
    
    /* Handling the case where the place if bigger than or
    equal to the list length, so it just places the value
    at the end of the list no matter how much bigger the
    placement spot is.*/
    int listLength = 1; // 1 based index
    while(walker->next)
    {
        walker = walker->next;
        listLength++;
    }
    if(place >= listLength + 1)
    {
        node *value = malloc(sizeof(node));
        value->data = val;          // assign value
        value->next = walker->next; // link to value next to walker
        walker->next = value;       // link walker to value.
        return;
    }

    // Reset walker
    walker = list;

    // Traverse to the position before the desired place
    for (int i = 1; i < place - 1; i++)
    {
        if (walker == NULL)
        {
            printf("Invalid place\n");
            return;
        }
        walker = walker->next;
    }

    // create new node to insert
    node *value = malloc(sizeof(node));
    value->data = val;          // assign value
    value->next = walker->next; // link to value next to walker
    walker->next = value;       // link walker to value.
}

// Function prints all values in a list.
void display(node *t)
{
    printf("\nPrinting your linked list....... ");

    while (t != NULL)
    {
        printf("%d ", t->data);
        t = t->next;
    }
}

int main()
{
    // declare root apprpriately
    node* root = NULL;

    int ch, ele, v;
    while (1)
    {
        printf("\nMenu: 1. insert at front, 2. reverse list 3. Insert to place 0. exit: \n");
        scanf("%d", &ch);
        if (ch == 0)
        {
            printf("\nGOOD BYE>>>>\n");
            break;
        }
        if (ch == 1)
        {
            printf("\nEnter data(an integer): ");
            scanf("%d", &ele);

            // call the funtion appropriately
            root = insert_front(root, ele);
            display(root);
        }
        if (ch == 2)
        {
            root = reverse(root);
            printf("List reversed.\n");

            // call the funtion appropriately
            display(root);
        }
        if (ch == 3)
        {
            printf("\nEnter data (an integer) and place (>1) separated by space: ");
            scanf("%d %d", &ele, &v);
            insertToPlace(root, ele, v);
            display(root);
        }
    }
    return 0;
}
