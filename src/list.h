#ifndef OS_PROJECT_LIST_H
#define OS_PROJECT_LIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>


// region TYPE DEFINITION

typedef struct Node {
    void *item;
    struct Node *next ;
} Node;

typedef Node *NodePtr;

typedef struct List {
    int count;
    struct Node *first;
    struct Node *last;
} List;

typedef List *ListPtr;

typedef void *VoidPtr;

typedef void (*fctPtr)(void *);

typedef enum {LESSER = -1, EQUAL = 0, GREATER = 1} cmpResult;

typedef cmpResult (*fctCmp)(void *, void*);

// endregion

// region METHOD DEFINITION

/**
 * @brief Create new list
 * @details Allocate memory and initialize the list
 * @return pointer to this allocated memory space
 */
ListPtr newList();

/**
 * @brief Destroy a list
 * @details Deallocate list' memory
 * @param list Object to freed
 */
void freeList(ListPtr list);

/**
 * @brief Add element at the end of the list
 * @details Allocate node memory, initialize it and link it to the last list' node
 * @param list List to modify
 * @param item Element to append
 * @return pointer to the newly created node
 */
NodePtr addListNode(ListPtr list, VoidPtr item);

/**
 * @brief Apply a function to each list' node
 * @param list List to modify
 * @param function Function to apply
 */
// void applyFunctionToList(ListPtr list, fctPtr function);

/**
 * @brief Delete a List' node
 * @details Remove list' node by deallocating memory and relinking list' nodes
 * @param list List to modify
 * @param node Node to delete
 */
// void deleteNodeFromList(ListPtr list, NodePtr node);

// endregion

// region ERROR DEFINITION

#define ERROR_CMPRESULT_INVALID "[ERROR] Unknown result value (=%d)"

// endregion

#endif /* OS_PROJECT_LIST_H */
