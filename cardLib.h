#ifndef ASS3_CARDLIB_H
#define ASS3_CARDLIB_H

#include <stdbool.h>

#include "nodeLib.h"

/*
 * Example data structure for the linked list
 */
typedef struct {
    int rank;
    char suit;
    char contents[3];
} Card;


bool card_comparison_function(GenericData *valOne, GenericData *targetValue);

bool card_rank_comparison_function(
        GenericData *value, GenericData *targetValue);

bool card_suit_comparison_function(
        GenericData *value, GenericData *targetValue);

//Card Printing Functions
void card_printing_function(void *value, FILE *outputStream);

char *string_card_hand_printing_function(void *value);

char *string_card_end_of_round_printing_function(void *value);

#endif //ASS3_CARDLIB_H
