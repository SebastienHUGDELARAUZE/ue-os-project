#include "liblist.h"
#include <criterion/criterion.h>

Test(LinkedList, list_init) {
    // ARRANGE
    ListPtr LinkedList = NULL;

    // ACT
    LinkedList = newList();

    // ASSERT
    cr_assert_not_null(LinkedList);
}

Test(LinkedList, list_add) {
    // ARRANGE
    ListPtr LinkedList = NULL;
    LinkedList = newList();
    char* value = "test";

    // ACT
    addListNode(LinkedList, value);

    // ASSERT
    cr_assert_eq(LinkedList->count, 1);
    cr_assert_str_eq(LinkedList->first->item, value);
}

Test(LinkedList, list_destroy) {
    // ARRANGE
    ListPtr LinkedList = NULL;
    LinkedList = newList();
    addListNode(LinkedList, "test");

    // ACT
    freeList(LinkedList);

    // ASSERT
}
