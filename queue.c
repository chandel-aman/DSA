// Implementation of queue using linked list

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure of linked list node to store queue elements
typedef struct linkedList
{
    int value;
    struct linkedList *next;
}Node;

// Structure of queue
typedef struct queue
{
    // front stores the front node of the linked list, and rear stores the rear/end node of the linked list
    Node *front, *rear;
} Queue;

// Creating a new linked list node
Node *newNode(int val)
{
    Node *ptr = (Node *)malloc(sizeof(Node));
    ptr->value = val;
    ptr->next = NULL;
    return ptr;
}

// Creating a new queue
Queue *newQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    // assigning the rear and front of the queue as null
    q->rear = q->front = NULL;
    return q;
}


// Function to check if the queue is empty
bool isEmpty(Node * ptr)
{
    if (ptr == NULL){
        return true;
    }
    return false;
}


// Function to display the whole queue
void displayQueue(Node * ptr){

    // check for empty queue
    if (isEmpty(ptr))
    {
        printf("The queue is empty!\n");
        return;
    }
    printf("Front -> ");
    while(ptr){
        printf("%d -> ", ptr->value);
        ptr = ptr->next;
    }
    printf("End\n");
}


// Function to add elements in queue
void enQueue(Queue *q, int val)
{
    // creating a new node
    Node* temp = newNode(val);

    if(temp == NULL){
        printf("Queue is full!\n");
    }

    // if the queue is empty then the front and rear of the queue are same
    if (isEmpty(q->front))
    {
        q->front = q->rear = temp;
        // q->front->next = NULL;
        // q->rear->next = NULL;
        return;
    }

    // if the queue has atleast one element
    q->rear->next = temp; // storing the address of new node in rear
    q->rear = temp;       // adding the new node in place of rear
}

// Function to delete an element from queue
void deQueue(Queue *q)
{
    // check for empty queue
    if (isEmpty(q->front))
    {
        printf("The queue is empty, can not delete!\n");
        return;
    }

    // if queue is not empty
    Node *temp = q->front;
    q->front = q->front->next;

    // front becomes NULL then rear also becomes NULL
    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    // freeing the node deleted
    free(temp);
}

// main function
void main()
{
    Queue *q = newQueue();
    
    int ch, val;
    do{
        printf("Enter\n\t1. to display the queue\n\t2. to add elements to the queue\n\t3. to remove element from the queue\n\t0. to exit\n\t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            displayQueue(q->front);
            break;
        case 2:
            printf("Enter the value to be inserted in the queue. ");
            scanf("%d", &val);
            enQueue(q, val);
            printf("%d has been inserted to the queue.\n", val);
            break;
        case 3:
            printf("%d has been removed from the queue.", q->front->value);
            deQueue(q);
            break;
        case 0:
            printf("Exited!\n");
            break;
        
        default: printf("Invalid input!\n");
            break;
        }
    }while(ch!=0);
    printf("Front %d\n", q->front->value);
    printf("Rear %d\n", q->rear->value);
}