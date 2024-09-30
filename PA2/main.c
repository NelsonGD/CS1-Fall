/*
Nelson Diaz
COP3502C - Programming Assignment 2
09/25/2024
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for student
typedef struct Student {
    int sequenceNumber;
    struct Student* next;
} Student;

// Queue structure for group
typedef struct Queue {
    Student* front;
    Student* rear;
    int nodeCount;
    int k;  // Skipping value
    int th; // Threshold value
    int garage; // Garage number
} Queue;

/* Function creates new student by dynamically allocating
mem. for student node. sequence num assigned to student.
Return pointer to new student node. */ 
Student* createStudent(int sequence) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    newStudent->sequenceNumber = sequence;
    newStudent->next = NULL;
    return newStudent;
}

/* Function to enqueue a student to the circular queue.
Add new student to queue as a ciruclar list. q points
to Queue for adding student. sequence is for num of
student enqueued */
void enqueue(Queue* q, int sequence) {
    Student* newStudent = createStudent(sequence);
    if (q->front == NULL) {
        q->front = q->rear = newStudent;
        q->rear->next = q->front; // Circular link
    } else {
        q->rear->next = newStudent;
        q->rear = newStudent;
        q->rear->next = q->front; // Circular link
    }
    q->nodeCount++;
}

/* Function to create a reverse circular linked list for the queue.
With loop it enqueues students from n to 1. */
void createReverseCircle(Queue* q, int n) {
    // Enqueue students from n down to 1
    for (int j = n; j >= 1; j--) {
        enqueue(q, j);
    }
}

/* Function to rearrange the circle to correct order.
Checks if queue empty or has node with three standard 
pointers. Updates front and rear. */
void rearrangeCircle(Queue* q) {
    if (q->front == NULL || q->front == q->rear) return;

    Student* prev = q->rear;
    Student* current = q->front;
    Student* next = NULL;
    Student* first = q->front;

    do {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } while (current != first);

    // Adjust front and rear
    q->rear = q->front;
    q->front = prev;
}

// Function to display the queue
void display(Queue* q) {
    if (q->front == NULL) return;

    // Print the garage number first
    printf("%d", q->garage);

    Student* temp = q->front;
    do {
        printf(" %d", temp->sequenceNumber);
        temp = temp->next;
    } while (temp != q->front);
    printf("\n");
}

/* Function to simulate phase 1 eliminations.
Continues until num of student in queue is threshold.
Skips k-1 students, eliminates k-th student and freeing it.
Updates front and rear ptrs. Decrements nodeCount. */
void phase1Elimination(Queue* q) {
    int k = q->k;
    int th = q->th;

    Student* prev = q->rear;
    Student* current = q->front;

    while (q->nodeCount > th) {
        for (int count = 1; count < k; count++) {
            prev = current;
            current = current->next;
        }
        // Eliminate current
        printf("Student# %d eliminated\n", current->sequenceNumber);
        prev->next = current->next;
        if (current == q->front) {
            q->front = current->next;
        }
        if (current == q->rear) {
            q->rear = prev;
        }
        free(current);
        q->nodeCount--;
        current = prev->next;
    }
}

/* Function to find the student with the highest sequence number in phase 2.
Finds student with highest sequence number in the front of its group.
Goes through queues, compares student at the front sequence number
to find max. Updates group index with garage number of group. */
Student* findMaxStudent(Queue queues[], int garageNumbers[], int* groupIndex) {
    Student* maxStudent = NULL;
    int minGarage = 11; // Set to maximum possible garage + 1

    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i] && queues[i].front != NULL) {
            if (maxStudent == NULL || queues[i].front->sequenceNumber > maxStudent->sequenceNumber ||
                (queues[i].front->sequenceNumber == maxStudent->sequenceNumber && i < minGarage)) {
                maxStudent = queues[i].front;
                minGarage = i;
            }
        }
    }

    *groupIndex = minGarage;
    return maxStudent;
}

/* Function to simulate phase 2 eliminations. Calculates
total number of students remaining. Keeps eliminating
until one student left using findMaxStudent then eliminating
that student from the group. Updates group queue and garageNumbers
if group empty. Decrements totalStudents. */
void phase2Elimination(Queue queues[], int garageNumbers[]) {
    int totalStudents = 0;
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i]) totalStudents += queues[i].nodeCount;
    }

    while (totalStudents > 1) {
        int groupIndex;
        Student* maxStudent = findMaxStudent(queues, garageNumbers, &groupIndex);
        printf("Eliminated student %d from group for garage %d\n", maxStudent->sequenceNumber, groupIndex);

        Student* eliminated = queues[groupIndex].front;
        if (queues[groupIndex].front == queues[groupIndex].rear) {
            queues[groupIndex].front = queues[groupIndex].rear = NULL;
            garageNumbers[groupIndex] = 0;
        } else {
            queues[groupIndex].front = queues[groupIndex].front->next;
            queues[groupIndex].rear->next = queues[groupIndex].front;
        }
        free(eliminated);
        queues[groupIndex].nodeCount--;
        totalStudents--;
    }
}

/* Function to free the entire queue. 
Goes through circular list and frees each node.
Makes front and rear equal to NULL at the end.*/
void freeQueue(Queue* q) {
    if (q->front == NULL) return;

    Student* current = q->front;
    Student* next;
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != q->front);
    q->front = q->rear = NULL;
}

// Main function to simulate the entire process
int main(void) {
    // reads number of groups
    int G;
    scanf("%d", &G);

    // initialize queues and garageNumbers arrays.
    Queue queues[11];
    // Initialize the queues
    for (int i = 0; i <= 10; i++) {
        queues[i].front = queues[i].rear = NULL;
        queues[i].nodeCount = 0;
        queues[i].k = 0;
        queues[i].th = 0;
        queues[i].garage = i;
    }

    int garageNumbers[11] = {0}; // Keep track of which garages are used

    /* reading inputs, gets garage number, number of students
    number for skipping, and threshold. Then initialize the
    queue for each group. Then "mark" the garage for being in use.
    Then create the reverse list of students. */ 

    for (int i = 0; i < G; i++) {
        int garage, n, k, th;
        scanf("%d %d %d %d", &garage, &n, &k, &th);
        queues[garage].front = queues[garage].rear = NULL;
        queues[garage].nodeCount = 0;
        queues[garage].k = k;
        queues[garage].th = th;
        queues[garage].garage = garage;
        garageNumbers[garage] = 1; // Mark this garage as used

        // Create reverse circle
        createReverseCircle(&queues[garage], n);
    }

    // Display initial status
    printf("Initial status of nonempty queues\n");
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i]) {
            display(&queues[i]);
        }
    }

    printf("\n");

    // Rearrange the circles to correct order
    printf("After ordering status of nonempty queues\n");
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i]) {
            rearrangeCircle(&queues[i]);
            display(&queues[i]);
        }
    }

    printf("\n");

    // Phase 1 elimination
    printf("Phase1 elimination\n\n");
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i]) {
            printf("Group for Garage# %d\n", i);
            phase1Elimination(&queues[i]);
            printf("\n");
        }
    }

    // Phase 2 elimination
    printf("Phase2 elimination\n");
    phase2Elimination(queues, garageNumbers);

    // Determine the winner
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i] && queues[i].front != NULL) {
            printf("\nStudent %d from the group for garage %d is the winner!\n", queues[i].front->sequenceNumber, i);
            break;
        }
    }

    // Free the queues
    for (int i = 1; i <= 10; i++) {
        if (garageNumbers[i]) {
            freeQueue(&queues[i]);
        }
    }

    return 0;
}