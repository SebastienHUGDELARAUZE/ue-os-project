#include "list.h"

// region PRIVATE DECLARATION
void permuteNodeValue(NodePtr currentNode);

typedef NodePtr *NodesPtr;
NodesPtr getNodesPtr(ListPtr);
// endregion

// region PUBLIC METHODS
ListPtr newList() {
    ListPtr list = malloc(sizeof(List));
    list->count = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void freeList(ListPtr list) {
    NodePtr *nodes = getNodesPtr(list);
    for (int node_index = 0; node_index < list->count; ++node_index)
        free(nodes[node_index]);
    free(list);
}

NodePtr addListNode(ListPtr list, VoidPtr item) {
    NodePtr node = malloc(sizeof(Node));
    node->item = item;
    node->next = NULL;

    if (list->count == 0) {  // Empty list
        list->first = list->last = node;
    } else { // Not empty list
        NodePtr previousNode = list->last;
        previousNode->next = list->last = node;
    }
    list->count++;

    return node;
}

void applyFunctionToList(ListPtr list, fctPtr function) {

}

void deleteNodeFromList(ListPtr list, NodePtr node) {

}
// endregion

// region PRIVATE METHODS
void permuteNodeValue(NodePtr currentNode) {
    VoidPtr currentNodeValue = currentNode->item;
    NodePtr nextNode = currentNode->next;
    VoidPtr nextNodeValue = nextNode->item;

    // PERMUTE CONTENT
    currentNode->item = nextNodeValue;
    nextNode->item = currentNodeValue;
}

NodePtr *getNodesPtr(ListPtr list) {
    NodePtr *nodes = malloc(sizeof(NodePtr) * list->count);

    NodePtr currentNode = list->first;
    for (int node_index = 0; currentNode; ++node_index) {
        nodes[node_index] = currentNode;
        currentNode = currentNode->next;
    }

    return nodes;
}
// endregion
