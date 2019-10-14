#include "nodeLib.h"

/*
 * Function for creating a string from a value (void*) which holds a string
 * (Used in string_print_list_of_node)
 *
 * Returns a pointer to the created string
 */
char *string_printing_function(void *value) {
    char *currentString = value;
    size_t stringLength = strlen(currentString) + strlen(" ");

    char *outputString = malloc(sizeof(char) * stringLength);

    snprintf(outputString, stringLength, "%s", currentString);

    return outputString;
}

/*
 * Allocates space for a dynamically sized LinkedList structure which has no
 * firstNode element.
 * Acts as a sort of pointer to the rest of the list and should not be removed
 * (or freed) until 'remove_all_nodes' has been called
 *
 * Returns pointer to the linked list head
 */
LinkedList *create_linked_list(GenericNodeFreeFunction nodeFreeFunction) {
    LinkedList *headNode = (LinkedList *) malloc(sizeof(LinkedList));
    headNode->firstNode = NULL;
    headNode->nodeFreeFunction = nodeFreeFunction;
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
int iterate_list(LinkedList *linkedList, GenericNodeFunction nodeFunction) {
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
 * Since the nodeLib works with generics, when printing, the amount of space
 * to allocate may not be known before hand e.g. dynamically sized strings
 *
 * This function takes a linked list and iterates through it with a generic
 * node function (in this case used to determine the number of chars needed
 * to print the LARGEST node in the list.
 *
 * Returns -1 if error encountered, number of chars otherwise
 */
int determine_max_node_print_size(LinkedList *linkedList,
        GenericNodeStringPrintFunction printingFunction) {
    if (linkedList == NULL){
        return -1;
    }
    if (count_number_of_nodes(linkedList) == 0){
        //no nodes therefore, unable to determine size of largest node
        return -1;
    }

    Node *tempNode = linkedList->firstNode;
    size_t stringLength = 0;
    int sizeOfLargestNode = 0;

    if (tempNode == NULL) {
        return -1;
    }

    while (tempNode->next != NULL) {
        char* formattedNode = printingFunction(tempNode->value);
        stringLength = strlen(formattedNode);
        free(formattedNode);

        if (stringLength > sizeOfLargestNode) {
            sizeOfLargestNode = stringLength;
        }
        tempNode = tempNode->next;
    }

    //Otherwise won't go to last one ever
    char* formattedNode = printingFunction(tempNode->value);
    stringLength = strlen(formattedNode);
    free(formattedNode);

    if (stringLength > sizeOfLargestNode) {
        sizeOfLargestNode = stringLength;
    }

    return sizeOfLargestNode;
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
        if (currentNode->head->nodeFreeFunction != NULL){
            currentNode->head->nodeFreeFunction(currentNode->value);
        }
        free(currentNode->value);
        free(currentNode);
    } else if ((currentNode->next == NULL) && (currentNode->previous !=
            NULL)) {
        //last node and not only node
        currentNode->previous->next = NULL;
        if (currentNode->head->nodeFreeFunction != NULL){
            currentNode->head->nodeFreeFunction(currentNode->value);
        }
        free(currentNode->value);
        free(currentNode);
    } else if ((currentNode->previous == NULL) && (currentNode->next ==
            NULL)) {
        //first and last and only node
        //update LinkedList headNode->firstNode
        currentNode->head->firstNode = NULL;
        if (currentNode->head->nodeFreeFunction != NULL){
            currentNode->head->nodeFreeFunction(currentNode->value);
        }
        free(currentNode->value);
        free(currentNode);
    } else {
        //not first, not last, not alone
        link_nodes(currentNode->previous, currentNode->next);
        if (currentNode->head->nodeFreeFunction != NULL){
            currentNode->head->nodeFreeFunction(currentNode->value);
        }
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
 * To account for variable length nodes, maximum chars per node is
 * calculated using determine_max_node_print_size() given as
 * maxCharsPerNode
 *
 * If the list is empty prints a new line character. todo
 */
char *string_print_list_of_nodes(LinkedList *headNode, char *delimiter,
        GenericNodeStringPrintFunction printingFunction) {

    Node *tempNode = get_first_node(headNode);

    if (tempNode == NULL) {
        return NULL; //checks if the list is empty
    }

    int maxCharsPerNode = determine_max_node_print_size(headNode,
            printingFunction);

    if (maxCharsPerNode < 0){
        return NULL; // checks that the max chars per node param is valid
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
            char *nodeString = printingFunction(tempNode->value);
            strcat(outputString, nodeString);
            free(nodeString);
            //appends the delimiter to outputString
            strcat(outputString, delimiter);
            tempNode = tempNode->next;
        }
    } while (tempNode->next != NULL);
    //appends the final node value to outputString
    char *nodeString = printingFunction(tempNode->value);
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
        GenericComparisonFunction comparisonFunction) {
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
 * Creates a storage array of the size of the linkedList.
 * Used for storing information about the linkedList e.g.
 * indices which match a value.
 */
int* create_storage_array(LinkedList* linkedList){
    if (linkedList == NULL){
        return NULL;
    }
    //Stores result of search by index. Can't be more indices than size of list
    int linkedListSize = count_number_of_nodes(linkedList);

    if (linkedListSize < 1){
        return NULL;
    }

    int *indexStorage = malloc(sizeof(int) * linkedListSize);
    for (int i = 0; i < linkedListSize; i++) {
        //Fill the array with -1 (acts as sentinel for invalid index)
        indexStorage[i] = -1;
    }

    return indexStorage;
}

/*
 * Searches through the list from the start for a specified value,
 * returns the indices of each occurrence into a storage array.
 *
 * Storage array should be at least the size of the array.
 *
 * (or -1 if value was not found in the list)
 */
int * find_all_indices_of_value(void *targetValue, LinkedList *linkedList,
        GenericComparisonFunction comparisonFunction) {

    int * indexStorage = create_storage_array(linkedList);
    if(indexStorage == NULL){
        return NULL;
    }

    int arrayPosition = 0;
    int nodeIndex = 0;
    bool isMatch;

    Node *tempNode = get_first_node(linkedList);
    if (tempNode == NULL) {
        return NULL;
    }

    do {
        if (tempNode->next != NULL) {
            isMatch = comparisonFunction(tempNode->value, targetValue);
            if (isMatch) {
                indexStorage[arrayPosition] = nodeIndex;
                arrayPosition++;
            }
            tempNode = tempNode->next;
            nodeIndex++;
        }
    } while (tempNode->next != NULL);

    isMatch = comparisonFunction(tempNode->value, targetValue);
    if (isMatch) {
        indexStorage[arrayPosition] = nodeIndex;
    }

    return indexStorage;
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
 * Takes a node number, a destination list and a starting list,
 * as well as a copying function to clone node values.
 * Remove the nth node from the originalList and adds it as the last node
 * on the destination list.
 *
 * Takes a genericCopyFunction
 *
 * Returns true on success or false otherwise e.g. if it encounters a null
 * (e.g. no elements in original list)
 */
bool transfer_nth_node(int nodeNumber, LinkedList *destinationList,
        LinkedList *originalList, GenericCopyFunction genericCopyFunction) {

    if (originalList == NULL || destinationList == NULL) {
        return false;
    }

    Node *tempNode = find_nth_node(nodeNumber, originalList);

    if (tempNode == NULL) {
        return false;
    }

    GenericData *copiedData = genericCopyFunction(tempNode->value);


    remove_node(tempNode);
    add_node(destinationList, copiedData);
    return true;
}

int find_index_of_lowest_valued_node(LinkedList* linkedList,
        GenericComparisonFunction comparisonFunction){
    int lowestValuedNodeIndex = 0;
    int currentNodeIndex = 0;
    bool isLesser;

    Node *tempNode = get_first_node(linkedList);
    if (tempNode == NULL) {
        return -1;
    }

    do {
        if (tempNode->next != NULL) {
            isLesser = comparisonFunction(tempNode->value,
                    get_value_of_nth_node(lowestValuedNodeIndex, linkedList));
            if (isLesser) {
                lowestValuedNodeIndex = currentNodeIndex;
            }
            tempNode = tempNode->next;
            currentNodeIndex++;
        }
    } while (tempNode->next != NULL);

    isLesser = comparisonFunction(tempNode->value,
            get_value_of_nth_node(lowestValuedNodeIndex, linkedList));
    if (isLesser) {
        lowestValuedNodeIndex = currentNodeIndex;
    }
    return lowestValuedNodeIndex;
}

/*
 * Non - in place sorting algorithm which creates a new list and populates
 * it by finding the lowest value from the original list (form comparison
 * function) - removes from the old list and adds to the new list.
 */
void sort_linked_list(LinkedList **originalList,
        GenericComparisonFunction comparisonFunction,
        GenericCopyFunction copyFunction,
        GenericNodeFreeFunction nodeFreeFunction) {
    if (*originalList == NULL){
        return;
    }
    if (count_number_of_nodes(*originalList) == 0){
        return;
    }

    LinkedList* sortedList = create_linked_list(nodeFreeFunction);

    while(count_number_of_nodes(*originalList) > 0){
        int lowest_val_node_index = find_index_of_lowest_valued_node(
                *originalList,
                comparisonFunction);
        transfer_nth_node(lowest_val_node_index, sortedList, *originalList,
                copyFunction);
    }

    delete_linked_list(*originalList);
    *originalList = sortedList;
}
