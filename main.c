#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

/*
 * Returns a LinkedList struct which has no firstNode element.
 * Acts as a sort of pointer to the rest of the list and should not be removed
 * (or freed) until 'remove_all_nodes'
 */
LinkedList* create_LinkedList(void){
    LinkedList* headNode = (LinkedList*) malloc(sizeof(LinkedList));
    headNode->firstNode = NULL;
    return headNode;
}

/*
 * Finds the last node and adds the newNode as the new tail
 * If the list is empty, sets the newNode as the first node.
 */
Node* add_node(LinkedList* linkedList, Card* card){
    Node* newNode = (Node*)malloc(sizeof(Node));

    //this linkedlist is currently empty
    if (linkedList->firstNode == NULL){
        newNode->value = card;
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->head = linkedList;

        linkedList->firstNode = newNode;
        return newNode;
    }

    Node * tempNode = get_last_node_from_node(linkedList->firstNode);

    newNode->next = NULL;
    newNode->value = card;
    newNode->head = linkedList;

    link_nodes(tempNode, newNode);
    return newNode;
}


void set_node_next(Node* currentNode, Node* nextNode){
    currentNode->next = nextNode;
}

void set_node_previous(Node* currentNode, Node* previousNode){
    currentNode->previous = previousNode;
}

//for nodes A, B sets A.firstNode = B, B.previous = A
void link_nodes(Node* previousNode, Node* nextNode){
    set_node_next(previousNode, nextNode);
    set_node_previous(nextNode, previousNode);
}

Node* get_first_node_from_node(Node* currentNode){
    Node* tempNode = currentNode;
    while(tempNode->previous != NULL){
        tempNode = tempNode->previous;
    }
    return tempNode;
}

Node* get_last_node_from_node(Node* currentNode){
    Node * tempNode = currentNode;
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
    }
    return tempNode;
}

Node* get_last_node(LinkedList* linkedList){
    Node * tempNode = linkedList->firstNode;

    if(tempNode == NULL){
        return NULL;
    }

    while(tempNode->next != NULL){
        tempNode = tempNode->next;
    }
    return tempNode;
}

Node* get_first_node(LinkedList* linkedList){
    //goes to the head of the list and returns the firstNode element
    Node* tempNode = linkedList->firstNode;
    return tempNode;
}


/*
 * Removes the specified node.
 *
 * Fixes next and previous for neighbouring nodes, assigns the head->next
 * Frees the memory allocated to the node AND the memory allocate to the value
 * of the node.
 */
void remove_node(Node* currentNode){
    if (currentNode == NULL){
        return;
    }

    //first node and not only node
    if((currentNode->previous == NULL) && (currentNode->next != NULL)){
        currentNode->next->previous = NULL;

        //update LinkedList headNode->firstNode
        currentNode->head->firstNode = currentNode->next;
        free(currentNode->value);
        free(currentNode);
    }
    //last node and not only
    else if ((currentNode->next == NULL) && (currentNode->previous != NULL)){
        currentNode->previous->next = NULL;
        free(currentNode->value);
        free(currentNode);
    }
    //first and last and only
    else if ((currentNode->previous == NULL) && (currentNode->next == NULL)){

        //update LinkedList headNode->firstNode
        currentNode->head->firstNode = NULL;
        free(currentNode->value);
        free(currentNode);
    }
    //not first, not last, not alone
    else {
        link_nodes(currentNode->previous, currentNode->next);
        free(currentNode->value);
        free(currentNode);
    }
}

void print_node_details(Node* currentNode) {
    if(currentNode == NULL){
        printf("Invalid call to print node details: pointer is null\n");
        return;
    }

    char nextNodeDetails[3];
    char previousNodeDetails[3];

    if (currentNode->next != NULL){
        strcpy(nextNodeDetails,currentNode->next->value->contents);
    }  else {
        strcpy(nextNodeDetails, "NA");
    }

    if (currentNode->previous != NULL){
        strcpy(previousNodeDetails,currentNode->previous->value->contents);
    }  else {
        strcpy(previousNodeDetails, "NA");
    }

    printf("Assigned head node?: %s\n", currentNode->head != NULL ?
    "true" :"false");
    printf("Head of list?: %s\n", currentNode->previous == NULL ? "true" :
    "false");
    printf("Tail of list?: %s\n", currentNode->next == NULL ? "true" :
    "false");
    printf("Previous: %s\n", previousNodeDetails);
    printf("Next: %s\n", nextNodeDetails);
    printf("Rank: %d\nSuit: %c\nContents: %s\n",
           currentNode->value->rank, currentNode->value->suit,
           currentNode->value->contents);
    printf("--------------------------------------------------\n");
}

void print_all_nodes_details(LinkedList* linkedList){
    Node * tempNode = get_first_node(linkedList);
    print_node_details(tempNode);
    while(tempNode->next != NULL){
        tempNode = tempNode->next;
        print_node_details(tempNode);
    }
}

void remove_all_nodes(Node* currentNode){
    if(currentNode == NULL){
        return;
    }
    Node * tempNode = get_first_node_from_node(currentNode);

    while(tempNode->next != NULL){
        remove_node(tempNode->previous);
        tempNode = tempNode->next;
        //todo simplify removal
        //otherwise misses second to last element
        if(tempNode->next == NULL){
            remove_node(tempNode->previous);
        }
    }
    remove_node(tempNode);
}

void delete_LinkedList(LinkedList* headNode){
    if(headNode->firstNode == NULL){
        free(headNode);
        return;
    }

    remove_all_nodes(headNode->firstNode);
    free(headNode);
}


int print_list_of_nodes(LinkedList* headNode){
    Node* tempNode = get_first_node(headNode);

    if (tempNode == NULL){
        printf("\n");
        return 1;
    }

    do {
        if (tempNode->next != NULL){
            printf("%s ", tempNode->value->contents);
            tempNode = tempNode->next;
        }
    } while (tempNode->next != NULL);

    printf("%s\n", tempNode->value->contents);

    return 0;
}

/*
 * Takes a file pointer and prints the contents of each node in list in order
 * from start to end in the form 1A2B3C
 *
 * Includes new line character at the end.
 */
int file_print_list_of_nodes(FILE* filePointer, LinkedList* headNode){
    Node* tempNode = get_first_node(headNode);

    if (tempNode == NULL){
        fprintf(filePointer,"\n");
        return 1;
    }

    do {
        if (tempNode->next != NULL){
            fprintf(filePointer,"%s", tempNode->value->contents);
            tempNode = tempNode->next;
        }
    } while (tempNode->next != NULL);

    fprintf(filePointer,"%s\n", tempNode->value->contents);

    return 0;
}

//uses array starting at one notation as n is based on human input
//nodeNumber should be between 1 and 6 inclusive
Node* find_nth_node(int nodeNumber, LinkedList* linkedList){
    Node* tempNode = get_first_node(linkedList);
    if (tempNode == NULL){
        return NULL; //the list is empty
    }

    for (int i = 1; i < nodeNumber; i++){
        if(tempNode->next == NULL){
            return NULL; //invalid index
        }
        tempNode = tempNode->next;
    }

    return tempNode;
}

Card* get_value_of_nth_node(int nodeNumber, LinkedList* linkedList){
    Node* tempNode = find_nth_node(nodeNumber, linkedList);

    if (tempNode == NULL) {
        return NULL;
    }

    return tempNode->value;
}

int remove_nth_node(int nodeNumber, LinkedList* linkedList){

    Node* tempNode = find_nth_node(nodeNumber, linkedList);
    remove_node(tempNode);

    return 0;
}

/*
 * Remove the last node from the originalList and adds it as the last node
 * on the destination list. Returns if it encounters a null (e.g. no
 * elements in original list)
 */
void transfer_last_node(LinkedList* destinationList, LinkedList* originalList){
    if(originalList == NULL || destinationList == NULL){
        return;
    }

    Node* tempNode = get_last_node(originalList);

    if(tempNode == NULL){
        return;
    }

    Card* copiedCard = (Card*)malloc(sizeof(Card));
    copyCard(copiedCard, tempNode->value);

    remove_node(tempNode);
    add_node(destinationList, copiedCard);
}


int main() {

    LinkedList* linkedListOne = create_LinkedList();
    LinkedList* linkedListTwo = create_LinkedList();

    Card* a = (Card*)malloc(sizeof(Card));
    a->suit = 'M';
    a->rank = '9';
    strcpy(a->contents, "9M");

    Card* b = (Card*)malloc(sizeof(Card));
    b->suit = 'M';
    b->rank = '9';
    strcpy(b->contents, "2F");

    Card* c = (Card*)malloc(sizeof(Card));
    c->suit = 'M';
    c->rank = '9';
    strcpy(c->contents, "CC");


    add_node(linkedListOne, a);
    add_node(linkedListTwo, b);

    printf("Original setup:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    transfer_last_node(linkedListTwo, linkedListOne);
    printf("Transferring last node from one to two:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    transfer_last_node(linkedListTwo, linkedListOne);
    printf("Transferring last node from one to two:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    transfer_last_node(linkedListOne, linkedListTwo);
    printf("Transferring last node from Two to One:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    transfer_last_node(linkedListOne, linkedListTwo);
    printf("Transferring last node from Two to One:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    printf("Adding a node cc to One:\n");
    add_node(linkedListOne, c);
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);

    transfer_last_node(linkedListTwo, linkedListOne);
    printf("Transferring last node from one to two:\n");
    printf("List One:");
    print_list_of_nodes(linkedListOne);
    printf("List Two:");
    print_list_of_nodes(linkedListTwo);


    transfer_last_node(linkedListTwo, NULL);
    transfer_last_node(NULL, linkedListOne);
    transfer_last_node(NULL, NULL);

    delete_LinkedList(linkedListOne);
    delete_LinkedList(linkedListTwo);

    //    Card a = {.rank = 1, .suit = 'A'};
//    strcpy(a.contents, "aa");
//
//    Card b = {.rank = 2, .suit = 'B'};
//    strcpy(b.contents, "bb");
//
//    Card c = {.rank = 3, .suit = 'C'};
//    strcpy(c.contents, "cc");
//
//    Card d = {.rank = 4, .suit = 'D'};
//    strcpy(d.contents, "dd");
//
//    Card e = {.rank = 5, .suit = 'E'};
//    strcpy(e.contents, "ee");

    return 0;
}