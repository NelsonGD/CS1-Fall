#include <stdlib.h>
#include <stdio.h>
#include "leak_detector_c.h"

struct node {
    int data;
    struct node* next;
};

struct node* insert(struct node* list, int d);
struct node* del(struct node* list, int d);
void print(struct node* list);
void freeList(struct node* list);
void copy(struct node* q, struct node** s);

int main(void) {
    int number = 0, choice = 0;
    struct node* pList = NULL;
    struct node* nList = NULL;

    // Let user add values until they enter -1
    while(choice != 4) {
        // Get operation.
        printf("\nDo you want to (1)insert, (2)delete, (3)copy (4)quit.\n");
        scanf("%d", &choice);

        // Execute operation
        if(choice == 1) {
            // Get the number.
            printf("Your choice is 1\nEnter the value to insert");
            scanf("%d", &number);
            pList = insert(pList, number);
            // Look at the list.
            printf("\nItems in linked list: ");
            print(pList);
        } else if(choice == 2) {
            // Get the number.
            printf("Your choice is 2\nEnter the value to delete.");
            scanf("%d", &number);
            pList = del(pList, number);
            // Look at the list
            printf("\nItems in linked list: ");
            print(pList);
        } else if(choice == 3) {
            if(nList)
                freeList(nList);
            copy(pList, &nList);
            printf("Your choice is 3\nItems in NEW linked list: ");
            print(nList);
        } else {
            break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("Your choice is 4\nBye..\n");

    return 0;
}

/* 
Insert a new node into the linked list. 
*/
struct node* insert(struct node* list, int d) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->data = d;
    newNode->next = NULL;

    // If the list is empty or the new node should be the first
    if (list == NULL || list->data >= d) {
        newNode->next = list;
        return newNode;
    }

    // Traverse the list to find the correct insertion point
    struct node* current = list;
    while (current->next != NULL && current->next->data < d) {
        current = current->next;
    }

    // Insert the new node in its sorted position
    newNode->next = current->next;
    current->next = newNode;

    atexit(report_mem_leak);
    return list;
}


/*
Prints the linked list by printing each node's data.
*/
void print(struct node* list) {
    if (list == NULL) {
        return;
    } else {
        printf("->%d", list->data); // Print data
        print(list->next);         // Recursive call to print the next node
    }
}

/*
Delete a node with value 'd' from the list.
*/
struct node* del(struct node* list, int d) {
    if (list == NULL)
        return NULL; // Corrected base case
    
    if (list->data == d) {
        struct node* temp = list;
        list = list->next; // Move list forward to exclude the node to be deleted
        free(temp);        // Free the node
        return list;       // Return the modified list
    }
    list->next = del(list->next, d); // Recursive call
    return list;
}

/*
Free all nodes in the linked list.
*/
void freeList(struct node* list) {
    if (list == NULL)
        return;

    freeList(list->next); // First free the rest of the list
    free(list);           // Then free the current node
}

/*
Copy the linked list.
*/
void copy(struct node* q, struct node** s) {
    if (q == NULL) {
        *s = NULL; // Base case: when the original list is empty
        return;
    }

    // Create new node for the copied list
    *s = malloc(sizeof(struct node));
    (*s)->data = q->data; // Copy data
    (*s)->next = NULL;

    // Recursive call to copy the next node
    copy(q->next, &((*s)->next));
}
