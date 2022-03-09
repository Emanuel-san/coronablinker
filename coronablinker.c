#include <stdio.h>
#include <stdlib.h>
#include "input.h"
//#include "list.h"
#include "heap.h"

#define DAYS_IN_RANGE 21

void handleChoice(void)
{
    int choice = 0;
    int idCode = 0, startCode = 0;
    int yourIdCode = 9999999;
    date newDate;
    // idList list = createList();
    idHeap heap = createHeap();
    char *filename = "IDCodes.txt";
    FILE *fileptr = fopen(filename, "r");
    if (fileptr == NULL)
    {
        printf("WARNING! Could not open file! Starting with empty list\n");
    }
    else
    {
        // list = listReadFromFile(fileptr, list);
        heapReadFromFile(fileptr, heap);
        fclose(fileptr);
        setToToday(&newDate);
        // deleteOldIdCodes(&list, getNDaysPrevious(newDate, DAYS_IN_RANGE));
        deleteOldIdData(heap, getNDaysPrevious(newDate, DAYS_IN_RANGE));
    }
    do
    {
        printf("1. Enter Startcode\n");
        printf("2. Enter ID code and date\n");
        printf("3. Receive alarm\n");
        printf("0. Quit\n");

        printf("Menu choice: ");
        char term;
        if (scanf("%d%c", &choice, &term) != 2 || term != '\n')
        {
            printf("Invalid choice!\n");
            fflush(stdin);
        }
        else
        {
            switch (choice)
            {
            case 1:
                enterStartCode(&startCode);
                if (startCode != 0)
                {
                    setToToday(&newDate);
                    // printListAll(list);
                    // deleteOldIdCodes(&list, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    deleteOldIdData(heap, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    // printListAll(list);
                    printf("Startcode: %d, your IDcode: %d.\n", startCode, yourIdCode);
                }
                break;

            case 2:
                enterIdCode(&idCode);
                if (idCode != 0)
                {
                    newDate = enterDate();
                    // createNewNode(&list, newDate, idCode);
                    heapInsert(heap, createIdDataElement(newDate, idCode));
                }
                break;

            case 3:
                enterIdCode(&idCode);
                if (idCode != 0)
                {
                    setToToday(&newDate);
                    // deleteOldIdCodes(&list, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    deleteOldIdData(heap, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    // if (isCodeInList(list, idCode))
                    if (isIdCodeinHeap(heap, idCode))
                    {
                        printf("You've been exposed to corona!\n");
                    }
                }
                break;

            case 0:
                fileptr = fopen(filename, "w");
                if (!fileptr)
                {
                    printf("Failed to open file for writing");
                }
                else
                {
                    setToToday(&newDate);
                    // deleteOldIdCodes(&list, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    deleteOldIdData(heap, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    // listWriteToFile(fileptr, list);
                    heap = heapSort(heap);
                    heapWriteToFile(fileptr, heap);
                    fclose(fileptr);
                }
                // destroyList(&list);
                heapDestroy(heap);
                printf("Good bye! Dont get sick, stay home, clean your hands, stay safe!\n");
                exit(1);

            default:
                printf("Invalid choice!\n");
            }
        }
    } while (1);
}

int main(void)
{

    handleChoice();

    return 0;
}