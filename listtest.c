#include "list.h"
#include "date.h"
#include <stdio.h>
#include "unittest.h"

idList tempListTest(idList header, int nodes)
{

    date newDate;
    int idCode = 1234546;
    setToToday(&newDate);

    for (int i = 0; i < nodes; i++)
    {
        createNewNode(&header, newDate, idCode);
        newDate = getPreviousDay(newDate);
        idCode += 212;
    }
    return header;
}

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

    TEST_CASE("Testing printListAll with more nodes");
    // Insert some more nodes
    list = tempListTest(list, 5);
    printListAll(list);

    TEST_CASE("Testing destroyList");
    destroyList(&list);
    VERIFY(listIsEmpty(list), "List is empty");

    TEST_CASE("Testing deletingOldIdCodes");
    list = tempListTest(list, 30);
    printListAll(list);
    printf("Deleting codes older then %d days\n", 20);
    setDate(&date1, 9, 2, 2022);
    deleteOldIdCodes(&list, getNDaysPrevious(date1, 20));

    printListAll(list);
    printf("Deleting codes older then %d days\n", 30);
    deleteOldIdCodes(&list, getNDaysPrevious(date1, 20));
    printListAll(list);

    return 0;
}