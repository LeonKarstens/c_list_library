#include "nodeLib.h"

/*
 * Allocates space for a dynamically sized LinkedList structure which has no
 * firstNode element.
 * Acts as a sort of pointer to the rest of the list and should not be removed
 * (or freed) until 'remove_all_nodes' has been called
 *
 * Returns pointer to the linked list head
 */
LinkedList *create_linked_list(void) {
    LinkedList *headNode = (LinkedList *) malloc(sizeof(LinkedList));
    headNode->firstNode = NULL;
    return headNode;
}

/*
 * Finds the last node and adds a newNode as the new tail.
 *
 * Takes a linkedList to add the node to and the GenericData to add to the list
 * If the list is empty, sets the newNode as the first node.
 *
 * Returns newly created node
 */
Node *add_node(LinkedList *linkedList, GenericData *genericData) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    //this linkedlist is currently empty
    if (linkedList->firstNode == NULL) {
        newNode->value = genericData;
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->head = linkedList;

        linkedList->firstNode = newNode;
        return newNode;
    }

    Node *tempNode = get_last_node_from_node(linkedList->firstNode);

    newNode->next = NULL;
    newNode->value = genericData;
    newNode->head = linkedList;

    link_nodes(tempNode, newNode);
    return newNode;
}

/*
 * Finds the first node and adds the newNode as the new head
 *
 * Takes a linkedList to add the node to and the GenericData to add to the list
 * If the list is empty, sets the newNode as the first node.
 *
 * Returns newly created node
 */
Node *add_node_to_start(LinkedList *linkedList, GenericData *genericData) {
    Node *newNode = (Node *) malloc(sizeof(Node));

    //if linkedlist is currently empty
    if (linkedList->firstNode == NULL) {
        newNode->value = genericData;
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->head = linkedList;

        linkedList->firstNode = newNode;
        return newNode;
    }

    Node *tempNode = linkedList->firstNode;

    newNode->value = genericData;
    link_nodes(newNode, tempNode);
    newNode->previous = NULL;
    newNode->head = linkedList;

    linkedList->firstNode = newNode;
    return newNode;
}

/*
 * Goes through each node of the list applying the function in the function
 * pointer. Returns the returns status of the function pointer
 *
 * If the list is empty, returns 0.
 */
int iterate_list(LinkedList *linkedList, int (*nodeFunction)(void *)) {
    Node *tempNode = linkedList->firstNode;
    int functionStatus = 0;
    int returnValue = 0;

    if (tempNode == NULL) {
        return 0;
    }

    while (tempNode->next != NULL) {
        returnValue = nodeFunction(tempNode->value);
        if (returnValue != 0) {
            functionStatus = returnValue;
        }

        tempNode = tempNode->next;

    }
    //Otherwise won't go to last one ever
    returnValue = nodeFunction(tempNode->value);
    if (returnValue != 0) {
        functionStatus = returnValue;
    }

    return functionStatus;
}

/*
 * Sets the next node of the given current node to the given next node.
 * Takes currentNode and nodeNode
 */
void set_node_next(Node *currentNode, Node *nextNode) {
    currentNode->next = nextNode;
}

/*
 * Sets the previous node of the given current node to the given previous node.
 */
void set_node_previous(Node *currentNode, Node *previousNode) {
    currentNode->previous = previousNode;
}


/*
 * For nodes (A, B) sets A.next = B, B.previous = A
 */
void link_nodes(Node *previousNode, Node *nextNode) {
    set_node_next(previousNode, nextNode);
    set_node_previous(nextNode, previousNode);
}

/*
 * Returns the first node in the given linked list from any node
 *
 * Takes (any) node in a linked list.
 */
Node *get_first_node_from_node(Node *currentNode) {
    Node *tempNode = currentNode;
    while (tempNode->previous != NULL) {
        tempNode = tempNode->previous;
    }
    return tempNode;
}

/*
 * Returns the last node in the linked list from any node
 *
 * Takes (any) node in a linked list
 */
Node *get_last_node_from_node(Node *currentNode) {
    Node *tempNode = currentNode;
    while (tempNode->next != NULL) {
        tempNode = tempNode->next;
    }
    return tempNode;
}

/*
 * Returns the last node in the given linked list
 *
 * Takes a LinkedList
 */
Node *get_last_node(LinkedList *linkedList) {
    Node *tempNode = linkedList->firstNode;

    if (tempNode == NULL) {
        return NULL;
    }

    while (tempNode->next != NULL) {
        tempNode = tempNode->next;
    }
    return tempNode;
}

/*
 * Returns the first node in the linked list
 */
Node *get_first_node(LinkedList *linkedList) {
    //goes to the head of the list and returns the firstNode element
    Node *tempNode = linkedList->firstNode;
    return tempNode;
}


/*
 * Removes the specified node from its linked list.
 *
 * Fixes next and previous for neighbouring nodes, assigns the head->next
 * Frees the memory allocated to the node AND the memory allocate to the value
 * of the node.
 */
void remove_node(Node *currentNode) {
    if (currentNode == NULL) {
        return;
    }

    //first node and not only node
    if ((currentNode->previous == NULL) && (currentNode->next != NULL)) {
        currentNode->next->previous = NULL;

        //update LinkedList headNode->firstNode
        currentNode->head->firstNode = currentNode->next;
        free(currentNode->value);
        free(currentNode);
    } else if ((currentNode->next == NULL) && (currentNode->previous !=
            NULL)) {
        //last node and not only node
        currentNode->previous->next = NULL;
        free(currentNode->value);
        free(currentNode);
    } else if ((currentNode->previous == NULL) && (currentNode->next ==
            NULL)) {
        //first and last and only node
        //update LinkedList headNode->firstNode
        currentNode->head->firstNode = NULL;
        free(currentNode->value);
        free(currentNode);
    } else {
        //not first, not last, not alone
        link_nodes(currentNode->previous, currentNode->next);
        free(currentNode->value);
        free(currentNode);
    }
}

/*
 * Using remove_node, removes (and frees) all of the nodes from a linked list
 *
 * Note: the LinkedList struct itself is not freed
 */
void remove_all_nodes(Node *currentNode) {
    if (currentNode == NULL) {
        return;
    }
    Node *tempNode = get_first_node_from_node(currentNode);

    while (tempNode->next != NULL) {
        remove_node(tempNode->previous);
        tempNode = tempNode->next;
        //otherwise misses second to last element
        if (tempNode->next == NULL) {
            remove_node(tempNode->previous);
        }
    }
    remove_node(tempNode);
}

/*
 * Removes all of the nodes from a linked list, frees them (using
 * remove_all_nodes) and frees the list
 *
 * Takes a linked list to remove
 *
 */
void delete_linked_list(LinkedList *headNode) {
    if (headNode->firstNode == NULL) {
        free(headNode);
        return;
    }

    remove_all_nodes(headNode->firstNode);
    free(headNode);
}

/*
 * Prints the list of nodes from a given linked list
 *
 * Takes the LinkedList to print
 *
 * If the list is empty prints a new line character.
 */
void print_list_of_nodes(LinkedList *headNode, FILE *outputStream,
        void(*printingFunction)(void *, FILE *)) {
    Node *tempNode = get_first_node(headNode);
//    fprintf(stderr, "Printing list of nodes:");
    if (tempNode == NULL) {
        fprintf(outputStream, "\n");
        return;
    }

    do {
        if (tempNode->next != NULL) {
            printingFunction(tempNode->value, outputStream);
            tempNode = tempNode->next;
        }
    } while (tempNode->next != NULL);

    printingFunction(tempNode->value, outputStream);
    fprintf(stderr, "\n");
}

/*
 * Prints the list of nodes from a given linked list to a string
 * Returns the string (or NULL if list is empty)
 *
 * prints in form:
 * "NxNxN"
 * where N is the the value of the nth node, x is the delimiter string
 *
 * Takes: the LinkedList to print, a string for the delimiter,
 * an int for the MAXIMUM number of chars per node, (e.g. for card where
 * contents is "SR" length is 2)
 * and an fp for interpreting how to print the node
 *
 * The string printing function should return a pointer to the string to add
 * to the output string based on the node.value supplied to it.
 *
 * To account for variable length nodes, chars per node parameter is given as
 * maxCharsPerNode (NOTE: if the max length of a node to be printed is unknown
 * then this function should not be used)
 *
 * If the list is empty prints a new line character.
 */
char *string_print_list_of_nodes(
        LinkedList *headNode,
        char *delimiter,
        int maxCharsPerNode,
        char *(*stringPrintFunction)(void *)) {

    Node *tempNode = get_first_node(headNode);
    //checks if the list is empty
    if (tempNode == NULL) {
        return NULL;
    }

    int numberOfNodes = count_number_of_nodes(headNode);
    size_t charsPerDelimiter = strlen(delimiter);

    size_t outputStringLength =
            maxCharsPerNode * numberOfNodes //chars in nodes
                    + (numberOfNodes - 1) * charsPerDelimiter //delimiters
                    + strlen(" "); //null terminator char

    char *outputString = calloc(outputStringLength, sizeof(char));

    do {
        if (tempNode->next != NULL) {
            //appends the string for node to outputString
            char *nodeString = stringPrintFunction(tempNode->value);
            strcat(outputString, nodeString);
            free(nodeString);
            //appends the delimiter to outputString
            strcat(outputString, delimiter);
            tempNode = tempNode->next;
        }
    } while (tempNode->next != NULL);
    //appends the final node value to outputString
    char *nodeString = stringPrintFunction(tempNode->value);
    strcat(outputString, nodeString);
    free(nodeString);

    return outputString;
}

/*
 * Returns the nth node from a linkedList
 *
 * Takes an integer (which should be between 1 and 6 for player decks) and a
 * LinkedList struct to get the node from
 *
 * Returns NULL if the node could not be retrieved
 *
 * Uses array starting at ZERO notation for nodeNumber
 */
Node *find_nth_node(int nodeNumber, LinkedList *linkedList) {
    Node *tempNode = get_first_node(linkedList);
    if (tempNode == NULL) {
        return NULL; //the list is empty
    }

    for (int i = 0; i < nodeNumber; i++) {
        if (tempNode->next == NULL) {
            return NULL; //invalid index
        }
        tempNode = tempNode->next;
    }

    return tempNode;
}

/*
 * Takes a node number (which signifies which element to fetch), and
 * linkedList which is the list the element is retrieved from.
 *
 * Returns value (the genericData stored) of the nth node from given
 * linked list or NULL if the element could not be retrieved
 */
GenericData *get_value_of_nth_node(int nodeNumber, LinkedList *linkedList) {
    Node *tempNode = find_nth_node(nodeNumber, linkedList);

    if (tempNode == NULL) {
        return NULL;
    }

    return tempNode->value;
}

/*
 * Searches through the list from the start for a specified value,
 * returning the first occurring index
 * (or -1 if value was not found in the list)
 */
int return_first_index_of_value(void *targetValue, LinkedList *linkedList,
        bool (*comparisonFunction)(GenericData *, GenericData *)) {
    int nodeIndex = 0;
    bool isMatch;

    Node *tempNode = get_first_node(linkedList);
    if (tempNode == NULL) {
        return -1;
    }

    do {
        if (tempNode->next != NULL) {
            isMatch = comparisonFunction(tempNode->value, targetValue);
            if (isMatch) {
                return nodeIndex;
            }

            tempNode = tempNode->next;
            nodeIndex++;
        }
    } while (tempNode->next != NULL);

    isMatch = comparisonFunction(tempNode->value, targetValue);
    if (isMatch) {
        return nodeIndex;
    } else {
        return -1;
    }
}

/*
 * Searches through the list from the start for a specified value,
 * returns the indices of each occurrence into a storage array.
 *
 * Storage array should be at least the size of the array.
 *
 * (or -1 if value was not found in the list)
 */
void find_all_indices_of_value(void *targetValue,
        LinkedList *linkedList, int *storageArray,
        bool (*comparisonFunction)(GenericData *, GenericData *)) {

    int arrayPosition = 0;
    int nodeIndex = 0;
    bool isMatch;

    Node *tempNode = get_first_node(linkedList);
    if (tempNode == NULL) {
        return;
    }

    do {
        if (tempNode->next != NULL) {
            isMatch = comparisonFunction(tempNode->value, targetValue);
            if (isMatch) {
                storageArray[arrayPosition] = nodeIndex;
                arrayPosition++;
            }
            tempNode = tempNode->next;
            nodeIndex++;
        }
    } while (tempNode->next != NULL);

    isMatch = comparisonFunction(tempNode->value, targetValue);
    if (isMatch) {
        storageArray[arrayPosition] = nodeIndex;
    }
}


/*
 * Removes the nth node form the list (and re-links the list as appropriate)
 *
 * Takes the nodeNumber (which signifies which element to remove) and the
 * linkedList to remove the element from.
 */
int remove_nth_node(int nodeNumber, LinkedList *linkedList) {

    Node *tempNode = find_nth_node(nodeNumber, linkedList);
    if (tempNode == NULL) {
        return 1;
    }

    remove_node(tempNode);

    return 0;
}

/*
 * Takes a linkedList and counts the number of nodes.
 *
 * Returns the number of nodes found in the given linked list (0 if list empty)
 */
int count_number_of_nodes(LinkedList *linkedList) {
    int nodeCount = 0;

    Node *tempNode = linkedList->firstNode;

    if (tempNode == NULL) {
        return nodeCount;
    }

    while (tempNode != NULL) {
        tempNode = tempNode->next;
        nodeCount++;
    }

    return nodeCount;
}

/*
 * Remove the last node from the originalList and adds it as the last node
 * on the destination list.
 *
 * Returns true on success or false otherwise e.g. if it encounters a null
 * (e.g. no elements in original list)
 */
bool transfer_last_node(LinkedList *destinationList, LinkedList *originalList,
        void(*generic_deep_copy(GenericData *, const GenericData *))) {

    if (originalList == NULL || destinationList == NULL) {
        return false;
    }

    Node *tempNode = get_last_node(originalList);

    if (tempNode == NULL) {
        return false;
    }

    GenericData *copiedData = (GenericData *) malloc(sizeof(GenericData));
    generic_deep_copy(copiedData, tempNode->value);

    remove_node(tempNode);
    add_node(destinationList, copiedData);
    return true;
}