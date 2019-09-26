#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cardLib.h"

void print_storage_array(int* storageArray){
    printf("[");
    for (int i = 0; i< 50; i++){
        if (storageArray[i] == -1){
            break;
        }
        printf("-%d-", storageArray[i]);
    }
    printf("]\n");
}


int main() {
    LinkedList* linkedListOne = create_linked_list();
    LinkedList* linkedListTwo = create_linked_list();
    int index;

    Card* a = malloc(sizeof(Card));
    a->suit = 'M';
    a->rank = '9';
    strcpy(a->contents, "M9");

    Card* b = malloc(sizeof(Card));
    b->suit = 'A';
    b->rank = '8';
    strcpy(b->contents, "A8");

    Card* c = malloc(sizeof(Card));
    c->suit = 'D';
    c->rank = '4';
    strcpy(c->contents, "D4");

    Card* d = malloc(sizeof(Card));
    d->suit = 'X';
    d->rank = '2';
    strcpy(d->contents, "X2");

    printf("Original setup:\n");
    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) a);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");








    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) b);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");





    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) c);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");

    printf("List One:");
    add_node_to_start(linkedListOne, (GenericData *) a);
    print_list_of_nodes(linkedListOne, stdout, card_printing_function);
    printf("\n");




    index = return_first_index_of_value(a, linkedListOne,
            card_comparison_function);
    printf("The index of %s was: %d\n", a->contents, index);

    index = return_first_index_of_value(c, linkedListOne,
            card_comparison_function);
    printf("The index of %s was: %d\n", c->contents, index);

    index = return_first_index_of_value(b, linkedListOne,
            card_comparison_function);
    printf("The index of %s was: %d\n", b->contents, index);

    index = return_first_index_of_value(d, linkedListOne,
            card_comparison_function);
    printf("The index of %s was: %d\n", d->contents, index);


    int storageArray[50];
    for (int i = 0; i< 50; i++){
        storageArray[i] = -1;
    }
    printf("The indices for entries with the suit %c are: ", d->suit);
    find_all_indices_of_value(d, linkedListOne, storageArray,
            card_suit_comparison_function);
    print_storage_array(storageArray);

    delete_linked_list(linkedListOne);
    delete_linked_list(linkedListTwo);

    return 0;
}