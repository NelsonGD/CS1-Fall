/* Nelson Diaz
10/01/24
COP3502C - Lab 6*/

#include <main.c>
#include <stdlib.h>

struct node{
    int data;
    struct node* next;
};

struct node* insert(struct node* list, int d);
struct node* del(struct node* list, int d);
void print(struct node* list);
void freeList(struct node* list);
void copy(struct node *q, struct node **s);

int main(void){
    int number = 0, choice = 0;
    struct node* pList = NULL;
    struct node* nList = NULL;

    // Let user add values until they enter -1
    while(choice != 4)
    {
        // Get operation.
        printf("\nDo you want to (1)insert, (2)delete, (3)copy, (4)quit.\n");
        scanf("%d", &choice);

        // Execute operation
        if(choice == 1)
        {
            // Get the number.
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
            // Look at the list.
            printf("Items in linked list: ");
            printf(pList);
        }else if(choice == 2){
            // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
            // Look at the list
            printf("Items in linked list: ");
            print(pList);
        }else if(choice == 3){
            if(nList)
                freeList(nList);
            copy(pList, &nList);
            printf("Items in NEW linked list: ");
            printf(nList);
        }else{
            break;
        }
    }
    freeList(nList);
    freeList(pList);
    printf("\nBye...\n");
}

/* 
1st: Check if the list is null, then create new node.
    If not, then insert the new node in the list.
*/
struct node* insert(struct node* list, int d){
    // The base case is null
    if(list == NULL){
        struct node* newNode = malloc(sizeof(struct node));
        newNode->data = d;
        newNode->next = NULL;
        return newNode;
    }

    list->next = insert(list->next, d);
    return list;
}

void print(struct node* list){
    if(list == NULL)
    {
        return;
    }else{
        printf("%d", list->next);print(list->next);
    }
}

struct node* del(struct node* list, int d)
{
    if(list == NULL)
        return;
    
    if(list->data == d)
    {
        // Copy node because you want return the node but keep the item.
        struct node* temp = list;
        list = list->next; // move list foward so it doesn't include the node to delete.
        free(temp); // Free node to delete
        return list; // return new list
    }
    list->next = del(list->next, d);
    return list;
}

void freeList(struct node* list)
{
    if(list == NULL)
        return;

    if(list->next != NULL)
    {
        struct node* temp = list;
        list = list->next;
        free(temp);
    }
    freeList(list->next);
}

void copy(struct node* q, struct node **s)
{
    struct node* copyList = malloc(sizeof(struct node));

}