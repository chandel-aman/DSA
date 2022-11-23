// stack using linked list
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// defining the structure of stack
typedef struct stack
{
    int value;
    struct stack *link;
} Node;

Node *Top = NULL;

// defining the structure of stack
Node *newNode(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        printf("Creation of node failed.\n");
        return NULL;
    }
    node->value = value;
    node->link = NULL;
    return node;
}

// function to push an element into the stack
void push(int value)
{
    Node *temp = newNode(value);
    // make the new node point to the top node
    temp->link = Top;
    // make the new node as the top node so that top always points to the last inserted data
    Top = temp;
}

// function to pop an element out of the stack
void pop()
{
    Node *temp;

    if (!Top)
    {
        printf("Stack is Empty!\n");
    }
    else
    {
        printf("Poped element = %d\n", Top->value);
        temp = Top;

        // change the Top by pointing it to the next node
        Top = Top->link;

        // free the poped node
        free(temp);
    }
}

// function to print the linked list
void print()
{
    Node *temp = Top;
    if (!temp)
    {
        printf("Stack is Empty\n");
    }
    else
    {

        // traverse through the stack
        while (temp)
        {
            printf("%d->", temp->value);
            temp = temp->link;
        }
        printf("NULL\n");
    }
}

void main(){
    print();
    push(10);
    push(20);
    push(30);
    print();
    pop();
    print();
}
