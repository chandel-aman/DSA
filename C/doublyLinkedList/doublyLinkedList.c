#include <stdio.h>
#include <stdlib.h>

//structure of doubly linked list
typedef struct doublyLinkedList
{
    int value;
    struct doublyLinkedList * prev;
    struct doublyLinkedList * next;
}Node;

//function to create a new node
Node * newNode(int val){
    //creating a node and allocating memory
    Node * node = (Node*)malloc(sizeof(Node));

    //if the node is null then the creation failed
    if(!node){
        printf("Node creation failure!\n");
        return NULL;
    }
    node->value = val;
    node->prev = node->next = NULL;
    return node;
}

//function to insert a new node at front
Node * insertAtFront(Node * head, int val){
    //new node creation
    Node * temp = newNode(val);

    //if the head is empty
    if(!head){
        head = temp;
        return head;
    }

    //if head is not empty
    
    //linking the first node with the new node
    temp->next = head;

    //storing new node in the prev pointer of current first node
    head->prev = temp;

    //pointing head to the new node
    head = temp;

    return head;
}

//function to add node at the end
Node * insertAtEnd(Node * head, int val){
    //new node creation
    Node * temp = newNode(val);

    //if the head is empty then add it to the head
    if(!head){
        head = temp;
        return head;
    }

    //else traverse to the lase node
    Node * ptr = head;
    
    while(ptr->next){
        ptr = ptr->next;
    }

    //linking the current last node with the new node
    ptr->next = temp;

    //linking the new node's previous pointer to the current last node
    temp->prev = ptr;

    return head;
}

//function to insert after a specified position
Node * insertBetween(Node * head, int val, int key, int pos){
    //if the list is empty then return null
    if(!head){
        printf("Empty list!\n");
        return NULL;
    }

    //pointer
    Node * ptr = head;

    //searching for the key element
    do{
        if(ptr->value == key){
            //creating a new node
            Node * temp = newNode(val);
            
            //if pos is +1 then insert after the key element
            if(pos == 1){
                //if the node is the last node
                if(!ptr->next){
                head = insertAtEnd(head, val);
                return head;
                }
                
                //linking the new node with the next node
                temp->next = ptr->next;
                //linking the new node with the key node
                temp->prev = ptr;

                //changing the next node's previous link
                ptr->next->prev = temp;

                //changing the key node's next link
                ptr->next = temp;

                return head;
            }
            //if pos is -1 then insert before the key
            if(pos == -1){
                //if the node is the first node
                if(!ptr->prev){
                head = insertAtFront(head, val);
                return head;
                }
                //linking the new node with the previous node
                temp->prev = ptr->prev;

                //linking the new node with the key node
                temp->next = ptr;

                //linking the previous node with the new node
                ptr->prev->next = temp;

                //linking the key node with the new node
                ptr->prev = temp;

                return head;
            }

        }
        else
        {
            ptr = ptr->next;
        }
    }while(ptr!= NULL);
    printf("%d not found.\n", key);
    return head;
}

//displaying the complete list
void displayList(Node * head){
    //if the list is empty
    if(!head){
        printf("Empyt list!\n");
        return;
    }

    Node * ptr = head;
    printf("\nHEAD ");
    while(ptr){
        printf(" <=> %d", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}

//function to delete an item from the list
Node * delete(Node * head, int key){
    //if the list is empty
    if(!head){
        printf("Empty list!\n");
        return head;
    }

    //pointer
    Node * ptr = head;

    //traverse the list and search for the key
    do{
        //if the key is present in the list
        if(ptr->value == key){
            //if it is the only node
            if(!ptr->prev && !ptr->next){
                head = NULL;
                printf("%d deleted.\n", ptr->value);
                free(head);
                return head;
            }

            //if the node to be delete is the first node
            if(!ptr->prev){
                ptr->next->prev = NULL;
                head = head->next;
                head->prev = NULL;
                printf("%d deleted.\n", ptr->value);
                free(ptr);
                return head;
            }

            //if the node to be delete is the last node of the list
            if(!ptr->next){
                printf("last\n");
                ptr->prev->next = NULL;
                printf("%d deleted.\n", ptr->value);
                free(ptr);
                return head;
            }
            //if the node to be delete is in between
            //linking the previous node with the next node
            ptr->prev->next = ptr->next;

            //linking the next node with the previous node
            ptr->next->prev = ptr->prev;

            printf("%d deleted.\n", ptr->value);
            free(ptr);
            return head;
        }
        ptr = ptr->next;
    }while(ptr);

    //else show appropriate message
    printf("%d not found.\n", key);
    return head;
}

//main funtion
void main(){
    Node * HEAD = NULL;
    
    int ch, val, key;
    do{
        printf("Enter\n\t1. to display the list\n\t2. to add item at beginning\n\t3. to add item at the end\n\t4. to add item before an item\n\t5. to add item after an item\n\t6. to delete an item\n\t0. to exit\n\t");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            displayList(HEAD);
            break;
        case 2:
            printf("Enter a number to be added. ");
            scanf("%d", &val);
            HEAD =  insertAtFront(HEAD, val);
            break;
        case 3:
            printf("Enter a number to be added. ");
            scanf("%d", &val);
            HEAD = insertAtEnd(HEAD, val);
            break;
        case 4:
            printf("Enter a number to be added. ");
            scanf("%d", &val);
            printf("Enter a number before which it has to be added. ");
            scanf("%d", &key);
            HEAD = insertBetween(HEAD, val, key, -1);
            break;
        case 5:
            printf("Enter a number to be added. ");
            scanf("%d", &val);
            printf("Enter a number after which it has to be added. ");
            scanf("%d", &key);
            HEAD = insertBetween(HEAD, val, key, 1);
            break;
        case 6:
            printf("Enter a number to be deleted. ");
            scanf("%d", &key);
            HEAD = delete(HEAD, key);
            break;
        case 0:
            printf("Exited!\n");
            break;        
        default:
            printf("Invalid input!\n");
            break;
        }
    }while(ch!=0);
}
