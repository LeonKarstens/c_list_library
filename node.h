#ifndef NODE_NODE_H
#define NODE_NODE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct Card {
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
    struct Node* firstNode;
} LinkedList;

typedef struct Node {
    Card* value;
    struct LinkedList* head;
    struct Node* next;
    struct Node* previous;
} Node;

void copyCard(Card* destinationCard, const Card* originalCard){
    destinationCard->rank = originalCard->rank;
    destinationCard->suit = originalCard->suit;
    destinationCard->contents[0] = originalCard->contents[0];
    destinationCard->contents[1] = originalCard->contents[1];
    destinationCard->contents[2] = '\0';
}

LinkedList* create_LinkedList(void);

void set_node_next(Node* currentNode, Node* nextNode);

void set_node_previous(Node* currentNode, Node* previousNode);

void link_nodes(Node* previousNode, Node* nextNode);

Node* get_first_node_from_node(Node* currentNode);

Node* get_last_node_from_node(Node* currentNode);

//finds the last node and adds the newNode as the new tail
Node* add_node(LinkedList* linkedList, Card* card);

//removes the specified node
void remove_node(Node* currentNode);


void print_node_details(Node* currentNode);


#endif //NODE_NODE_H
