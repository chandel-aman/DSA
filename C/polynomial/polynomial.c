// Polynomial multiplication using linked list

#include <stdio.h>
#include <stdlib.h>

// structure of linked list
typedef struct LinkedList
{
    int coeff, exp;
    struct LinkedList *next;
} Node;

// function to create a new node
Node *newNode(int c, int e, Node *head)
{
    // creating a new node and allocating memory
    Node *node = (Node *)malloc(sizeof(Node));

    if (!node)
    {
        printf("Node creation failure!\n");
        return NULL;
    }

    node->coeff = c;
    node->exp = e;
    node->next = NULL;
    // if head is empty add a new node to the head
    if (!head)
    {
        head = node;
    }
    else
    {
        Node *ptr = head;

        // traverse to the end of the list
        while (ptr->next)
        {
            if (ptr->exp < e)
            {
                node->next = ptr->next;
                ptr->next = node;
                return head;
            }
            else if (ptr->exp == e)
            {
                ptr->coeff += c;
                return head;
            }
            else
                ptr = ptr->next;
        }

        // adding the new node at the end of the list
        ptr->next = node;
    }
    return head;
}

// display the polynomial
void displayPoly(Node *head)
{
    if (!head)
    {
        printf("No polynomial found!\n");
        return;
    }

    // if head is not empty
    Node *ptr = head;
    while (ptr)
    {
        if (ptr->exp == 0)
        {
            printf("%d", ptr->coeff);
        }
        else if (ptr->exp == 1)
        {
            printf("%dX + ", ptr->coeff);
        }
        else
        {
            if (ptr->next)
                printf("%dX^%d + ", ptr->coeff, ptr->exp);
            else
                printf("%dX^%d", ptr->coeff, ptr->exp);
        }

        ptr = ptr->next;
    }
    printf("\n");
};

// function to multiply two polynomials and store it in a new list given
Node *multiplyPoly(Node *poly1, Node *poly2, Node *poly3)
{
    // check for empty lists
    if (!poly1 || !poly2)
    {
        printf("Multiplication is not possible!\n");
        return NULL;
    }

    // declaring pointers
    Node *ptr1 = poly1;
    Node *ptr2 = poly2;

    // multiplying each term of first polynomial with every term of second polynomial
    while (ptr1)
    {
        while (ptr2)
        {
            int c, e;
            c = ptr1->coeff * ptr2->coeff;
            e = ptr1->exp + ptr2->exp;
            poly3 = newNode(c, e, poly3);

            ptr2 = ptr2->next;
        }

        // assigning ptr2 to first head
        ptr2 = poly2;

        // iterating terms of polynomial 1
        ptr1 = ptr1->next;
    }

    return poly3;
}

// function to merge terms with same exponents
void mergePolyTerms(Node *head)
{
    // otherwise check for repeated terms
    Node *ptr1 = head, *ptr2, *dup;

    // traverse the list
    while (ptr1 && ptr1->next)
    {
        ptr2 = ptr1;
        while (ptr2->next)
        {
            if (ptr1->exp == ptr2->next->exp)
            {
                dup = ptr2->next;
                ptr1->coeff += ptr2->next->coeff;
                // deleting the repeated term
                ptr2->next = ptr2->next->next;
                free(dup);
            }
            else
                ptr2 = ptr2->next;
        }
        // traversing the polynomial
        ptr1 = ptr1->next;
    }
}

// main function
void main()
{
    Node *Poly1 = NULL;
    Node *Poly2 = NULL;
    Node *Poly3 = NULL;

    Poly1 = newNode(1, 2, Poly1);
    Poly1 = newNode(2, 1, Poly1);
    Poly1 = newNode(1, 0, Poly1);

    Poly2 = newNode(3, 3, Poly2);
    Poly2 = newNode(5, 1, Poly2);
    Poly2 = newNode(-9, 0, Poly2);

    Poly3 = multiplyPoly(Poly1, Poly2, Poly3);
    mergePolyTerms(Poly3);

    displayPoly(Poly1);
    displayPoly(Poly2);
    displayPoly(Poly3);
}
