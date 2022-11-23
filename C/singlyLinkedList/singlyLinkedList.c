#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// defining the structure of linked list
typedef struct linkedList
{
    int value;
    struct linkedList *next;
} Node;

// function to create a node
Node *newNode(int val)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        printf("Node creation of node failed!");
        return NULL;
    }
    node->value = val;
    node->next = NULL;
    return node;
}

// function to insert a new node at the begining of the list
Node *insertAtBeginning(Node *head, int val)
{
    Node *temp = newNode(val);
    // if the list is empty add a new node
    if (!head)
    {
        head = temp;
        return head;
    }

    // if the list is not empty add at the front
    // pointing the new node to the first node
    temp->next = head;
    // pointing head to the new node
    head = temp;

    return head;
}

// function to insert at the end at the list
Node *insertAtEnd(Node *head, int val)
{
    // if the list is empty
    if (!head)
    {
        head = insertAtBeginning(head, val);
        return head;
    }

    // if the list is not empty
    // traverse to the last node
    Node *temp = newNode(val);
    Node *ptr = head;
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    ptr->next = temp;
    return head;
}

// function to insert at any position in the list
Node *insertAtPosition(Node *head, int val, int key)
{
    // if the list is empty
    if (!head)
    {
        printf("The list is empty!\n");
        return NULL;
    }

    // creating a new node
    Node *temp = newNode(val);
    // creating a pointer
    Node *ptr = head;

    // if the list is not empty

    // if the node is to be inserted at a specified position
    int pos = 1; // assigning the position to be the first node
    // traverse to the key node
    while (key != pos && ptr->next)
    {
        pos++;
        ptr = ptr->next;
    }
    temp->next = ptr->next;
    ptr->next = temp;

    // if the node is to be inserted after a specified value
    // traverse while searching for the value in the list
    // while (ptr->next && ptr->value != key)
    // {
    //     ptr = ptr->next;
    // }
    // temp->next = ptr->next;
    // ptr->next = temp;

    return head;
}

// function to delete a node with given value
Node *delete (Node *head, int key)
{
    // if the list is empty
    if (!head)
    {
        printf("Empty list!\n");
        return NULL;
    }

    // if the list is not empty
    bool found = false;
    /*If the position is specified then search with index*/
    int pos = 1;
    // creating a pointer to the list
    Node *ptr = head;

    // if key is the head node
    if (key == 1)
    {
        head = ptr->next;
        free(ptr);
        return head;
    }

    // traversing the list
    do
    {
        if (pos + 1 == key){
            ptr->next = ptr->next->next;
            found = true;
            break;
        }
        pos++;
        ptr = ptr->next;
    } while (ptr->next);

    if (!found)
    {
        printf("The specified node not found!\n");
        return NULL;
    }

    /*If the value is specified then search the values in the list*/
    // traversing the list
    // while (!ptr->next && key != ptr->next->value)
    // {
    //     ptr = ptr->next;
    //     if (key == pos)
    //         found = true;
    // }
    // if (!found)
    // {
    //     printf("The specified node not found!\n");
    //     return NULL;
    // }
    // ptr->next = ptr->next->next;

    return head;
}

// function to display the complete list
void displayList(Node *head)
{
    // if the list is empty
    if (!head)
    {
        printf("Empyt list!\n");
        return;
    }

    Node *ptr = head;
    printf("\nHEAD ");
    while (ptr)
    {
        printf(" => %d", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

// function to clear the complete list
Node *clear(Node *head)
{
    Node *ptr = head, *temp;
    while (ptr)
    {
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
    head = NULL;
    return head;
}

// function to merge two given list
Node *mergeLists(Node *head1, Node *head2, Node *head3)
{
    // creating 2 pointers for the respective 2 heads
    Node *ptr1 = head1;
    Node *ptr2 = head2;
    Node *ptr3 = head3;
    while (!ptr1)
    {
        ptr3->value = ptr1->value;
        ptr3 = ptr3->next;
        ptr1 = ptr1->next;
    }
    while (!ptr2)
    {
        ptr3->value = ptr2->value;
        ptr3 = ptr3->next;
        ptr2 = ptr2->next;
    }

    return head3;
}

// function to reverse a linked list
Node *reverse(Node *head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;
    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    return head;
}

// function to search an element in a linked list
bool isPresent(Node *head, int key)
{
    Node *ptr = head;
    while (ptr)
    {
        if (ptr->value == key)
            return true;
        ptr = ptr->next;
    }
    return false;
}

// function to swap two nodes
void swap(Node *n1, Node *n2)
{
    int temp = n1->value;
    n1->value = n2->value;
    n2->value = temp;
}

// function to sort the list using a sorting algorithm
void sort(Node *head)
{
    int swapped;
    Node *ptr1 = head;
    Node *ptr2 = NULL;
    if (!head)
    {
        return;
    }
    do
    {
        swapped = 0;
        ptr1 = head;
        while (ptr1->next != ptr2)
        {
            if (ptr1->value > ptr1->next->value)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        ptr2 = ptr1;
    } while (swapped);
}

// main function
void main()
{
    Node *HEAD = NULL;
    int choice, val, key;
    while (choice != 0)
    {
        printf("Enter your choice\n\t1. Display list\n\t2. Add an element at end.\n\t3. To add an element at the beginnig.\n\t4. To add an element after a node.\n\t5. Remove an element\n\t6. Clear list\n\t7. To reverse the list\n\t8. To search a value\n\t9. To sort the list\n\t0. To exit\n\t");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayList(HEAD);
            break;
        case 2:
            printf("Enter value to insert. ");
            scanf("%d", &val);
            HEAD = insertAtEnd(HEAD, val);
            break;
        case 3:
            printf("Enter a value to insert at the end.");
            scanf("%d", &val);
            HEAD = insertAtBeginning(HEAD, val);
            break;
        case 4:
            printf("Enter a value to be inserted.");
            scanf("%d", &val);
            // printf("Enter the node after which it has to be inserted");
            printf("Enter the position of node after which it the given value has to be inserted.");
            scanf("%d", &key);
            HEAD = insertAtPosition(HEAD, val, key);
            break;
        case 5:
            // printf("Enter the number to be deleted.");
            printf("Enter the position to be deleted.");
            scanf("%d", &val);
            HEAD = delete (HEAD, val);
            break;
        case 6:
            HEAD = clear(HEAD);
            free(HEAD);
            break;
        case 7:
            HEAD = reverse(HEAD);
            break;
        case 8:
            printf("Enter a value to be searched.");
            scanf("%d", &key);
            if (isPresent(HEAD, key))
            {
                printf("%d is present in the list.", key);
            }
            else
            {
                printf("%d is not present in the list.", val);
            }
            break;
        case 9:
            sort(HEAD);
            printf("Sorted!");
            break;
        case 0:
            printf("Exited");
            break;
        default:
            printf("Invalid input!");
        }
    }
}
