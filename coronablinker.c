#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    FILE *fileptr = fopen(filename, "rb");
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
        // heapPrint(heap);
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
                    // setToToday(&newDate);
                    //  printListAll(list);
                    //  deleteOldIdCodes(&list, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    // deleteOldIdData(heap, getNDaysPrevious(newDate, DAYS_IN_RANGE));
                    //  printListAll(list);
                    printf("Reporting own device %d to server with start code %d.\n", yourIdCode, startCode);
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
                fileptr = fopen(filename, "wb");
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

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        handleChoice();
    }
    else
    {
        int yourIdCode = 9999999;
        date newDate, todaysDate;
        idHeap heap = createHeap();
        char *filename = "IDCodes.txt";

        if (!strcmp(argv[1], "add")) // strcmp returns 0 if strings are equal
        {
            if (argc != 4)
            {
                printf("Wrong amount of arguments for 'add' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7)
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else
            {
                newDate = convertStringToDate(argv[3]);

                if (!checkDate(newDate) || isDateInFuture(newDate))
                {
                    printf("Invalid date!");
                }
                else
                {
                    FILE *fileptr = fopen(filename, "rb");
                    heapReadFromFile(fileptr, heap);
                    fclose(fileptr);

                    heapInsert(heap, createIdDataElement(newDate, atoi(argv[2])));
                    setToToday(&todaysDate);
                    deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                    fileptr = fopen(filename, "wb");
                    heapWriteToFile(fileptr, heap);
                    fclose(fileptr);
                    printf("Registered interaction with device %d on ", atoi(argv[2]));
                    printFiStd(newDate);
                }
            }
        }
        else if (!strcmp(argv[1], "sick"))
        {
            if (argc != 3)
            {
                printf("Wrong amount of arguments for 'sick' command, type 'help' for available commands");
            }
            else if (!validStartcode(atoi(argv[2])) || strlen(argv[2]) > 6)
            {
                printf("Invalid start code, has to be exactly 6 numbers");
            }
            else
            {
                printf("Reporting own device %d to server with start code %d", yourIdCode, atoi(argv[2]));
            }
        }
        else if (!strcmp(argv[1], "check"))
        {
            FILE *fileptr = fopen(filename, "rb");
            if (argc != 3)
            {
                printf("Wrong amount of arguments for 'check' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7)
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else if (fileptr == NULL)
            {
                printf("No data stored on device\n");
            }
            else
            {
                heapReadFromFile(fileptr, heap);
                setToToday(&todaysDate);
                deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                // heapPrint(heap2);
                if (isIdCodeinHeap(heap, atoi(argv[2])))
                {
                    printf("You've been exposed to corona!");
                }
                else
                {
                    printf("Code not found");
                }
            }
            fclose(fileptr);
        }
        else if (!strcmp(argv[1], "debug"))
        {
            FILE *fileptr = fopen(filename, "rb");
            if (fileptr == NULL)
            {
                printf("No data stored on device\n");
            }
            else
            {
                heapReadFromFile(fileptr, heap);
                setToToday(&todaysDate);
                deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                printf("Stored data\n");
                heapPrint(heap);
            }
            fclose(fileptr);
        }
        else if (!strcmp(argv[1], "help"))
        {
            printf("Valid commands are:\ncoronablinker.exe add <device id> dd.mm.yyyy\ncoronablinker.exe sick <startcode>\ncoronablinker.exe check <device id>\ncoronablinker.exe debug\n");
        }
        else
        {
            printf("Unkown argument, type 'help' for available commands");
        }
    }

    return 0;
}