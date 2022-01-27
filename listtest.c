#include "list.h"
#include "input.h"
#include <stdio.h>

#define TEST_CASE(name) printf("\nRUNNING CASE: %s\n", name)
#define VERIFY(cond, msg)             \
    if (cond)                         \
        printf("SUCCESS: %s\n", msg); \
    else                              \
        printf("FAIL: %s\n", msg);

int main(void)
{
    idList list;
    date date1;
    setToToday(&date1);
    int idCode = 1234567;

    TEST_CASE("Testing createList and listIsEmpty");
    list = createList();
    VERIFY(listIsEmpty(list), "List is empty");

    TEST_CASE("Testing createNewNode and listIsEmpty");
    createNewNode(&list, date1, idCode);
    VERIFY(!listIsEmpty(list), "List is not empty");

    TEST_CASE("Testing printListAll");
    printListAll(list);

    // Insert some more nodes
    date1 = getPreviousDay(date1);
    createNewNode(&list, date1, idCode + 4157);
    date1 = getPreviousDay(date1);
    createNewNode(&list, date1, idCode + 25698);
    date1 = getPreviousDay(date1);
    createNewNode(&list, date1, idCode + 5658421);
    date1 = getPreviousDay(date1);
    createNewNode(&list, date1, idCode + 1);

    TEST_CASE("Testing printListAll with more nodes");
    printListAll(list);

    return 0;
}