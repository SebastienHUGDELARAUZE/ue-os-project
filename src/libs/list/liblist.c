#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include "liblist.h"

// region PRIVATE DECLARATION
void permuteNodeValue(NodePtr currentNode);

typedef NodePtr *NodesPtr;
NodesPtr getNodesTable(ListPtr list);
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
    NodePtr *nodes = getNodesTable(list);

    for (int node_index = 0; node_index < list->count; ++node_index) {
        free(nodes[node_index]);
    }
    free(list);
    free(nodes);
}

void freeItemList(ListPtr list, fctFree freeItem) {
    VoidTablePtr items = getItemsTable(list);
    
    for (int node_index = 0; node_index < list->count; ++node_index) {
        freeItem(items[node_index]);
    }
    free(items);
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

NodePtr getListNode(ListPtr list, fctCmp isNodeCmpFct, VoidPtr targetItem) {
    NodePtr nodeLookup = list->first;

    while (nodeLookup) {
        if (isNodeCmpFct(nodeLookup->item, targetItem)) return nodeLookup;
        nodeLookup = nodeLookup->next;
    }
    return NULL;
}

// void applyFunctionToList(ListPtr list, fctPtr function) {

// }

void deleteNodeFromList(ListPtr list, NodePtr node) {

}

VoidTablePtr getItemsTable(ListPtr list) {
    VoidTablePtr items = calloc(sizeof(VoidPtr), list->count);

    NodePtr currentNode = list->first;
    for (int node_index = 0; currentNode; ++node_index) {
        items[node_index] = currentNode->item;
        currentNode = currentNode->next;
    }

    return items;
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

NodePtr *getNodesTable(ListPtr list) {
    NodePtr *nodes = calloc(sizeof(NodePtr), list->count);

    NodePtr currentNode = list->first;
    for (int node_index = 0; currentNode; ++node_index) {
        nodes[node_index] = currentNode;
        currentNode = currentNode->next;
    }

    return nodes;
}
// endregion
