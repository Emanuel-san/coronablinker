#include "list.h"
#include "input.h"

int main(void)
{
    idList list = createList();
    date newDate;
    setToToday(&newDate);
    // int idCode;

    createNewNode(&list, newDate, 345345);
    createNewNode(&list, newDate, 345346);
    createNewNode(&list, newDate, 2354235);
    createNewNode(&list, newDate, 4564356);
    createNewNode(&list, newDate, 3464356);
    createNewNode(&list, newDate, 456456);

    printListAll(list);
}