#ifndef OS_PROJECT_LIST_H
#define OS_PROJECT_LIST_H

// #define ERROR_CMPRESULT_INVALID "[ERROR] Unknown result value (=%d)"

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
typedef VoidPtr *VoidTablePtr;

typedef bool (*fctCmp)(void*, void*);
typedef void (*fctFree)(void *);


/**
 * @brief Create new list
 * @details Allocate memory and initialize the list
 * @return pointer to this allocated memory space
 */
extern ListPtr newList();

/**
 * @brief Destroy a list
 * @details Deallocate list' memory
 * @param list Object to freed
 */
extern void freeList(ListPtr list);

extern void freeItemList(ListPtr list, fctFree freeItem);

/**
 * @brief Add element at the end of the list
 * @details Allocate node memory, initialize it and link it to the last list' node
 * @param list List to modify
 * @param item Element to append
 * @return pointer to the newly created node
 */
extern NodePtr addListNode(ListPtr list, VoidPtr item);

/**
 * @brief Search for a target item in the list
 * @details Iterate through list, using for each node the comparaison function
 * @param list List to search
 * @param isNodeCmpFct Function used to find the target node
 * @param targetItem Value used with the compare function
 * @return pointer to the target node, else NULL
 */
extern NodePtr getListNode(ListPtr list, fctCmp isNodeCmpFct, VoidPtr targetItem);

/**
 * @brief Apply a function to each list' node
 * @param list List to modify
 * @param function Function to apply
 */
// extern void applyFunctionToList(ListPtr list, fctPtr function);

/**
 * @brief Delete a List' node
 * @details Remove list' node by deallocating memory and relinking list' nodes
 * @param list List to modify
 * @param node Node to delete
 */
// extern void deleteNodeFromList(ListPtr list, NodePtr node);

VoidTablePtr getItemsTable(ListPtr list);

#endif /* OS_PROJECT_LIST_H */
