// Example of how to implement a queue with a linked list. 
#include <stdio.h>
#include<stdlib.h>

#define EMPTY -1

// Stores one node of the linked list.
typedef struct node {
    int data;
    struct node* next;
}node;

// Stores our queue.
typedef struct queue {
    struct node* front;
    struct node* back;
}queue;

void init(struct queue* qPtr);
int enqueue(struct queue* qPtr, int val);
int dequeue(struct queue* qPtr);
int empty(struct queue* qPtr);
int front(struct queue* qPtr);
void displayQueue(struct queue* MyQueuePtr);

int main() {
    
    // Allocate space for our queue and initialize it.
    struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
    
    init(MyQueuePtr);

    int choice;
    int data;

    int i;
    
    while (1)
    {
        printf("\n1.Insert element to queue \n");
        printf("2.Delete element from queue \n");
        printf("3. Display all elements of queue \n");
        printf("4.Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 1:
                printf("\nWhat data you want to put in the queue?: ");
                scanf("%d", &data);
                enqueue(MyQueuePtr, data);
                displayQueue(MyQueuePtr);
                break;
            case 2:
                data = dequeue(MyQueuePtr);
                if(data!=EMPTY)
                {
                    printf("\n%d deleted from queue\n", data);
                    displayQueue(MyQueuePtr);
                }
                else
                  printf("Empty queue\n");
                break;
            case 3:
                displayQueue(MyQueuePtr);
                break;
            case 4:
                exit(1);
            default:
                printf("Wrong choice \n");
        } /*End of switch*/
    } /*End of while*/
    return 0;
} /*End of main()*/

// Not changing queue so you just need to pass the address.
//! Passing whole structures is very INEFFICIENT
void displayQueue(struct queue* MyQueuePtr)
{
  struct node *t =  MyQueuePtr->front;

  while(t)
  {
    printf("%d ", t->data);
    t = t->next;
  }
  
}
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
//                 empty queue.
void init(struct queue* qPtr) {
     
   
}

// Pre-condition: qPtr points to a valid struct queue and val is the value to
//                enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
//                 no change will be made to the queue and 0 will be returned.
int enqueue(struct queue* qPtr, int val) 
{
    if(q->rear < MAX)
    {
        qPtr -> queue[qPtr->back] = item;
        qPtr -> rear++;
    }
    
    // No change to the queue was made because we couldn't find space for our
    // new enqueue.
    else
    {
        printf("FULL\n");
        return 0;   
    }
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
//                 at the front of the queue is deleted from the queue and 
//                 returned. Otherwise, -1 is returned to signify that the queue
//                 was already empty when the dequeue was attempted.
int dequeue(struct queue* qPtr) {
    // save front item to temp variable because you want to return the front
    if(q->front == q-> rear) // check if empty
    {
        printf("EMPTY\n");
        return EMPTY; 
    }

    int retval = qPtr -> queue_array[qPtr->front];
    qPtr -> front++;
    return retval;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int empty(struct queue* qPtr) {
   
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value 
//                 stored at the front of the queue is returned. Otherwise,
//                 -1 is returned to signify that this queue is empty.
int peek(struct queue* qPtr) {
    
}
