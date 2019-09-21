#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Data that is non specific (void pointer) so that anything can be stored
 * in linked list
 */
typedef void *GenericData;

/*
 * Example data structure for the linked list
 */
typedef struct {
    int rank;
    char suit;
    char contents[3];
} Card;

/*
 * The LinkedList is a special type of sentinel for the doubly linked list of
 * nodes. Even when there are no Nodes present, the LinkedList remains
 *
 * The LinkedList has a 'firstNode' to the first node in the list,
 * but the LinkedList is not assigned at previous to any node.
 *
 * To access the LinkedList, node->head is used.
 */
typedef struct LinkedList {
    struct Node *firstNode;
} LinkedList;

/*
 * The node element of a linked list which store the values.
 *
 * Each node stores a pointer to a card struct, a link to the following node,
 * the previous node and the LinkedList 'head' of the list.
 */
typedef struct Node {
    GenericData *value;
    struct LinkedList *head;
    struct Node *next;
    struct Node *previous;
} Node;

void card_printing_function(void* value, FILE* outputStream);

bool card_comparison_function(GenericData * valOne, GenericData * valTwo);

LinkedList *create_linked_list(void);

void delete_linked_list(LinkedList *headNode);

void file_print_list_of_nodes(FILE *outputStream, LinkedList *headNode);

int count_number_of_nodes(LinkedList *linkedList);

void set_node_next(Node *currentNode, Node *nextNode);

void set_node_previous(Node *currentNode, Node *previousNode);

void link_nodes(Node *previousNode, Node *nextNode);

Node *get_first_node(LinkedList *linkedList);

Node *get_last_node(LinkedList *linkedList);

Node *get_first_node_from_node(Node *currentNode);

Node *get_last_node_from_node(Node *currentNode);

//finds the last node and adds the newNode as the new tail
Node *add_node(LinkedList *linkedList, GenericData *genericData);

GenericData *get_value_of_nth_node(int nodeNumber, LinkedList *linkedList);

int remove_nth_node(int nodeNumber, LinkedList *linkedList);

//removes the specified node
void remove_node(Node *currentNode);

Node *add_node_to_start(LinkedList *linkedList, GenericData *genericData);

bool transfer_last_node(LinkedList *destinationList,
        LinkedList *originalList,
        void(*genericDeepCopy(GenericData *destination,
                const GenericData *original)));

void print_list_of_nodes(LinkedList *headNode, FILE* outputStream,
        void (*printingFunction)(void*, FILE *pFILE));

int iterate_list(LinkedList *linkedList, int (*functionPointer)(void *));

int return_index_of_value(void * targetValue, LinkedList* linkedList,
        bool (*comparisonFunction)(GenericData* valOne, GenericData*valTwo));

#endif //NODE_NODE_H
