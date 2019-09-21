#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

int main() {
    LinkedList* linkedListOne = create_linked_list();
    LinkedList* linkedListTwo = create_linked_list();
    int index;

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

    Card* d = malloc(sizeof(Card));
    d->suit = 'X';
    d->rank = '4';
    strcpy(d->contents, "X4");

    printf("Original setup:\n");
    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) a);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");




    index = return_index_of_value(a, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", a->contents, index);

    index = return_index_of_value(c, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", c->contents, index);

    index = return_index_of_value(b, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", b->contents, index);

    index = return_index_of_value(d, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", d->contents, index);





    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) b);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");



    index = return_index_of_value(a, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", a->contents, index);

    index = return_index_of_value(c, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", c->contents, index);

    index = return_index_of_value(b, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", b->contents, index);

    index = return_index_of_value(d, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", d->contents, index);



    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) c);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");




    index = return_index_of_value(a, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", a->contents, index);

    index = return_index_of_value(c, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", c->contents, index);

    index = return_index_of_value(b, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", b->contents, index);

    index = return_index_of_value(d, linkedListOne, card_comparison_function);
    printf("The index of %s was: %d\n", d->contents, index);

    delete_linked_list(linkedListOne);
    delete_linked_list(linkedListTwo);

    return 0;
}