#include <stdio.h>
#include <stdlib.h>
#define MAX 5
#define EMPTY -9999

// Defining the strucutre of a queue
typedef struct Queue
{
    int queue_array[MAX];
    int rear;
    int front;
}Queue;

void initQ(Queue *q){
    q->front = 0;
    q->rear = 0;
}

void enQueue(Queue *q, int item)
{
    if(q->rear < MAX) // Making sure that there is space.
    {    
        // You want to add an item, where? The rear back position.
        q->queue_array[q->rear] = item;
        // You just added something to the rear, so increment rear.
        q->rear++; // Not very same, if you are not making sure there is space
    }else{
        printf("FULL\n");
    }
}

// Recieves reference of a queue and does deQueue
int deQueue(Queue *q)
{
    /* If rear and front are in the same place that 
    means that the queue is empty */
    // Always check if the queue is empty
    if(q->rear == q->front){
        printf("EMPTn");
        return EMPTY;
    } // You don't have to do it since you already have a return in the if statement.
    // This mean that you want to return the front item.
    // Then you have to save the front, and make sure you are not deleting it.
    int retval = q->queue_array[q->front];
    q->front++; // Now the next item becomes the front
    return retval; 
}

/* Is the display function changing the queue? No
This means you don't have to pass the a pointer, but
passing the address of the queue is more EFFICIENT.
Instead of passing a whole structure you are just
passing reference that allows the funciton to access it.*/
void display(Queue *q)
{
    int i;
    if(q->front == q->rear)
        printf("Queue is empty\n");
    else{
        printf("\nQueue is: \n");
        // display the array from front to the rear
        for(i = q->front; i < q->rear; i++)
            printf("%d ", q->queue_array[i]);
        printf("\n\n");
    }
}

int main(void)
{
    int choice, data;

    Queue myQ; // You will have an array, front, and back.
    // After getting one queue, front and back are GARBAGE, so initialize them with a function.
    initQ(&myQ); // Initializing the front and back of the queue to 0, done statically so you need to pass address.

    while(1)
    {
        printf("1. Insert element to queue \n");
        printf("2. Delete element from queue\n");
        printf("3. Display all elements of queue\n");
        printf("4.Quit\n");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("\nWhat data you want to put in queue?:");
                scanf("%d", &data);
                enQueue(&myQ, data);
                display(&myQ);
                break;
            case 2:
                printf("%d deleted from the queue", myQ.queue_array[0]);
                deQueue(&myQ);
                display(&myQ);
            case 3:
                printf("Queue: ");
                display(&myQ);
                break;
            case 4:
                printf("Bye!\n");
                return 0;
                break;
        }
    }
    
    // If you want 10 queues, what do you do?
    Queue myBigQueue[10]; // This will give you 10 queues.
    // To initialize 10 different queues just call it 10
    // different times, so loop 10 times for each queue.

    return 0;
}