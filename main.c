#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

int main() {

    LinkedList* linkedListOne = create_linked_list();
    LinkedList* linkedListTwo = create_linked_list();

    Card* a = malloc(sizeof(Card));
    a->suit = 'M';
    a->rank = '9';
    strcpy(a->contents, "9M");

    Card* b = malloc(sizeof(Card));
    b->suit = 'M';
    b->rank = '9';
    strcpy(b->contents, "2F");

    Card* c = malloc(sizeof(Card));
    c->suit = 'M';
    c->rank = '9';
    strcpy(c->contents, "CC");

    printf("Original setup:\n");
    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) a);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);

    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) b);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);

    printf("List One:");
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    add_node_to_start(linkedListOne, (GenericData *) c);

    printf("List One:");
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);

//
//    add_node(linkedListOne, a);
//    add_node(linkedListTwo, b);
//
//    printf("Original setup:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    transfer_last_node(linkedListTwo, linkedListOne);
//    printf("Transferring last node from one to two:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    transfer_last_node(linkedListTwo, linkedListOne);
//    printf("Transferring last node from one to two:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    transfer_last_node(linkedListOne, linkedListTwo);
//    printf("Transferring last node from Two to One:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    transfer_last_node(linkedListOne, linkedListTwo);
//    printf("Transferring last node from Two to One:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    printf("Adding a node cc to One:\n");
//    add_node(linkedListOne, c);
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//    transfer_last_node(linkedListTwo, linkedListOne);
//    printf("Transferring last node from one to two:\n");
//    printf("List One:");
//    print_list_of_nodes(linkedListOne);
//    printf("List Two:");
//    print_list_of_nodes(linkedListTwo);
//
//
//    transfer_last_node(linkedListTwo, NULL);
//    transfer_last_node(NULL, linkedListOne);
//    transfer_last_node(NULL, NULL);

    delete_linked_list(linkedListOne);
    delete_linked_list(linkedListTwo);

    return 0;
}