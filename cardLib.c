#include "cardLib.h"

/*
 * Function for printing a card's contents from a node.
 * (Used in print list of node when working with cards)
 */
void card_printing_function(void *value, FILE *outputStream) {
    Card *currentCard = value;
    fprintf(outputStream, "%s ", currentCard->contents);
}

/*
 * Function for creating a string for a card's content from a  card node.
 * Used by hub to create player hand strings
 * (Used in create_string_from_list when working with cards)
 */
char *string_card_hand_printing_function(void *value) {
    Card *currentCard = value;
    size_t stringLength = strlen(currentCard->contents) + strlen(" ");

    char *outputString = malloc(sizeof(char) * stringLength);

    snprintf(outputString, stringLength, "%s", currentCard->contents);

    return outputString;
}

/*
 * Function for creating a string from a card's content from a node.
 * Used by playerLib to create end of round strings for players
 * (Used in create_string_from_list when working with cards)
 */
char *string_card_end_of_round_printing_function(void *value) {
    Card *currentCard = value;
    size_t stringLength = strlen("C.5 ");

    char *outputString = malloc(sizeof(char) * stringLength);

    snprintf(outputString, stringLength, "%c.%c", currentCard->suit,
            currentCard->rank);

    return outputString;
}

/*
 * Compares the strings (contents) of two cards to check if they are equivalent
 *
 * Used in return_first_index_of_value()
 */
bool card_comparison_function(GenericData *value, GenericData *targetValue) {
    Card *cardOne = (Card *) value;
    Card *cardTwo = (Card *) targetValue;

    if (strcmp(cardOne->contents, cardTwo->contents) == 0) {
        return true;
    } else {
        return false;
    }
}

/*
 * Compares the suits of two cards to check if they are equivalent
 *
 * Used in return_first_index_of_value()
 *
 * Takes (Card*, char*) as parameters
 */
bool card_suit_comparison_function(GenericData *value,
        GenericData *targetValue) {

    Card *cardOne = (Card *) value;
    char targetSuit = *(char *) targetValue;

    if (cardOne->suit == targetSuit) {
        return true;
    } else {
        return false;
    }
}

/*
 * Compares the ranks of two cards to check if valOne (cardOne has a LOWER
 * rank)
 *
 * Used in return_first_index_of_value()
 *
 * Takes Card*, int* as parameters
 */
bool card_rank_comparison_function(GenericData *value,
        GenericData *targetValue) {
    Card *cardOne = (Card *) value;
    int targetRank = *(int *) targetValue;

    if (cardOne->rank < targetRank) {
        return true;
    } else {
        return false;
    }
}