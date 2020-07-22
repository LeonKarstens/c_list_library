#ifndef ASS4_NODELIB_H
#define ASS4_NODELIB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * Data that is non specific (void pointer) so that anything can be stored
 * in linked list (including pointers to structs)
 */
typedef void *GenericData;

/*
 * A function pointer which takes a void pointer (could be a pointer to
 * anything and returns an int (used as a status indicator based on the
 * functions success or failure)
 *
 * Used in iterate_list to apply a given function to each element in the list
 */
typedef int (*GenericNodeFunction)(void *);

/*
 * A function which takes a void * (could be a pointer to anything,
 * including a struct).
 *
 * Frees the dynamically allocated elements of the data referenced by the
 * void *.
 */
typedef void (*GenericNodeFreeFunction)(void *);

/*
 * A function which takes a GenericData type (the value stored by a node)
 * and returns a string representation of the given value
 */
typedef char* (*GenericNodeStringPrintFunction)(void *);

/*
 * Function pointer for comparing two genericData elements, returns a bool
 * based on the outcome of the comparison
 */
typedef bool (*GenericComparisonFunction)(
        GenericData *valOne,
        GenericData *valTwo);

/*
 * Function pointer for copying a value of Generic Data type (similar to
 * clone or deep copy),
 * returns a pointer to cloned data
 */
typedef GenericData *(*GenericCopyFunction)(GenericData *value);

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
    GenericNodeFreeFunction nodeFreeFunction;
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

char *create_string_from_string_node(void *value);

//Linked List functions
LinkedList *create_linked_list(GenericNodeFreeFunction nodeFreeFunction);

Node *add_node_to_start(LinkedList *linkedList, GenericData *genericData);

void print_list_of_nodes(LinkedList *headNode, FILE *outputStream,
        void(*printingFunction)(void *, FILE *));

void delete_linked_list(LinkedList *headNode);

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

char *create_string_from_list(LinkedList *headNode, char *delimiter,
        GenericNodeStringPrintFunction printingFunction);

int iterate_list(LinkedList *linkedList, GenericNodeFunction nodeFunction);

int return_first_index_of_value(void *targetValue, LinkedList *linkedList,
        GenericComparisonFunction comparisonFunction);

int * find_all_indices_of_value(void *targetValue, LinkedList *linkedList,
        GenericComparisonFunction comparisonFunction);

void sort_linked_list(LinkedList **originalList,
        GenericComparisonFunction comparisonFunction,
        GenericCopyFunction copyFunction,
        GenericNodeFreeFunction nodeFreeFunction);

void sort_linked_list_alternative(LinkedList *currentList,
        GenericComparisonFunction comparisonFunction);

#endif //ASS4_NODELIB_H
