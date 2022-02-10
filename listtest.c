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

bool isDateInList(idList header, date date)
{
    idNode *currentNode = header;
    while (currentNode != NULL)
    {
        if (isEqual(currentNode->data.date, date))
        {
            return true;
        }
        else
        {
            currentNode = currentNode->next;
        }
    }
    return false;
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
    // printListAll(list);
    printf("Deleting codes older then %d days\n", 20);
    setDate(&date1, 9, 2, 2022);
    deleteOldIdCodes(&list, getNDaysPrevious(date1, 20));
    VERIFY(!isDateInList(list, getNDaysPrevious(date1, 21)), "All dates older than 20 deleted");

    // printListAll(list);
    printf("Deleting codes older then %d days\n", 10);
    deleteOldIdCodes(&list, getNDaysPrevious(date1, 10));
    VERIFY(!isDateInList(list, getNDaysPrevious(date1, 11)), "All dates older than 10 deleted");
    // printListAll(list);

    TEST_CASE("Testing isCodeInList");
    idCode = 1235394;
    VERIFY(isCodeInList(list, idCode), "ID code is in list");
    idCode = 9999999;
    VERIFY(!isCodeInList(list, idCode), "ID code is not in list");
    return 0;
}