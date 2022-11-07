#include <stdio.h>
#include <stdlib.h>

//structure of linked list
typedef struct circularLinkedList
{
    int value;
    struct circularLinkedList * next;
}Node;

//new node creation
Node * newNode(int val){
    Node * ptr = (Node*)malloc(sizeof(Node));
    if(!ptr){
        perror("Node creation failure!");
        return NULL;
    }
    ptr->value = val;
    ptr->next = NULL;
    return ptr;
}

//adding node to an empty list
Node * addToEmpty(Node * last, int val){
    //creating a new node
    Node * temp = newNode(val);

    //assigning last to the new node
    last = temp;

    //linking new node to last
    temp->next = last;

    return last;
}

//inserting at the begining of the list
Node * addAtStart(Node * last, int val){
    //if last is empty
    if(!last){
        last = addToEmpty(last, val);
        return last;
    }
    //if last is not null
    Node * temp = newNode(val);

    //linking new node to the first node
    temp->next = last->next;            //last has the link of the first node

    //linking last to the new node
    last->next = temp;

    return last;
}

//inserting at the end of the list
Node * addAtEnd(Node * last, int val){
    //if the list is empty
    if(!last){
        last = addToEmpty(last, val);
        return last;
    }

    //creating new node
    Node * temp = newNode(val);

    //linking the first node with the new node
    temp->next = last->next;

    //changing the link of last to the new node
    last->next = temp;

    //adding the new node at the end
    last = temp;

    return last;
}


//inserting at a specified position of the list
Node * addAtPos(Node * last, int val, int item){
    //if the list is empty return null with apt msg
    if(!last){
        printf("Empty list!\n");
        return NULL;
    }

    // //creating a new node
    // Node * temp = newNode(val);

    //first node
    Node * ptr = last->next;

    do{
        //if the item is present in the list then insert it after that node
        if(ptr->value == item){
            //new node
            Node * temp = newNode(val);

            //linking the new node with the next node
            temp->next = ptr->next;

            //linking the specified node to the new node
            ptr->next = temp;

            //if the specified node is the last node of the list then change the last to new node
            if(ptr == last){
                last = temp;
            }

            return last;
        }
        //traversing to the next node
        ptr = ptr->next;
    }while(ptr != last->next);

    //if the specified item is not present in the list
    printf("%d not present in the list!", item);
}

//function to delete the node
void delete(Node * last, int key){
    //check whether the list is empty or not
    if(!last){
        printf("Empty list!\n");
        return;
    }

    //if the item to be deleted is the first node
    if(last->next->value == key){
        last->next = last->next->next;
        printf("%d deleted.\n", key);
        free(last->next);
        return;
    }

    //first node
    Node * temp = last->next;
    //if the item to be deleted is the last node
    if(last->value == key){
        while(temp->next != last){
            temp = temp->next;
        }
        //linking the second last node to the first node
        temp->next = last->next;
        printf("%d deleted.\n", key);
        //freeing the last node
        free(last);
    }

    //if the item to be deleted is a node in between

    //last node
    Node * ptr = last;
    while(temp->value != key){
        temp = temp->next;
        ptr = ptr->next;
    }
    ptr->next = temp->next;
    printf("%d deleted.\n", key);
    free(temp);
}

//function to traverse the linked list
void display(Node * last){
    //if the list is empty
    if(!last){
        printf("Empty list!\n");
        return;
    }

    //first node
    Node * temp = last->next;

    do{
        printf("%d ", temp->value);
        temp = temp->next;
    }while(temp != last->next);
    printf("\n");
}


//main function
void main(){
    Node * last = NULL;

    int ch, val, key;
    do{
        printf("Enter\n\t1. to display the list\n\t2. to add item at the end\n\t3. to add item at the begining\n\t4. to add item at a specified position\n\t5. to delete an item\n\t0. to quit\n");
        scanf("%d", &ch);
        switch (ch){
            case 1:
                display(last);
                break;
            case 2:
                printf("Enter an item to inserted. ");
                scanf("%d", &val);
                last = addAtEnd(last, val);
                break;
            case 3:
                printf("Enter an item to inserted. ");
                scanf("%d", &val);
                last = addAtStart(last, val);
                break;
            case 4:
                printf("Enter an item to inserted. ");
                scanf("%d", &val);
                printf("Enter the item after which it has to be inserted. ");
                scanf("%d", &key);
                last = addAtPos(last, val, key);
                break;
            case 5:
                printf("Enter an item to be deleted. ");
                scanf("%d", &key);
                delete(last, key);
                break;
            case 0:
                printf("Exited!\n");
                free(last);
                break;
            default:
                printf("Invalid input!\n");
        }
    }while(ch!=0);
}
