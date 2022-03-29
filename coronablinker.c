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
                    heap = heapInsert(heap, createIdDataElement(newDate, idCode));
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
                    idData d;
                    d.idCode = idCode;
                    if (lookupOnSecond(heap, d))
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
    if (argc == 1) // Visual interactive terminal
    {
        handleChoice();
    }
    else
    {
        int yourIdCode = 9999999;
        date newDate, todaysDate;
        idHeap heap = createHeap();
        char *filename = "IDCodes.txt";

        /* STRCMP RETURNS 0 IF STRINGS ARE EQUAL*/
        if (!strcmp(argv[1], "add")) // add <idcode> <date> -- Insert new device interaction into the heap and store to file
        {
            if (argc != 4)
            {
                printf("Wrong amount of arguments for 'add' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7) // valid id code and length
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else
            {
                newDate = convertStringToDate(argv[3]); // convert the date from a string to a date data type

                if (!checkDate(newDate) || isDateInFuture(newDate)) // check that date is valid
                {
                    printf("Invalid date!");
                }
                else
                {
                    // If there is stored data in a file then read that data into a heap first...
                    FILE *fileptr = fopen(filename, "rb");
                    heapReadFromFile(fileptr, heap);
                    fclose(fileptr);

                    //...and then insert the new data into the heap...
                    heap = heapInsert(heap, createIdDataElement(newDate, atoi(argv[2])));
                    setToToday(&todaysDate);
                    // ...delete old id data based of n amount of days in range...
                    deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                    // ...and write is back to file.
                    fileptr = fopen(filename, "wb");
                    heapWriteToFile(fileptr, heap);
                    fclose(fileptr);
                    printf("Registered interaction with device %d on ", atoi(argv[2]));
                    printFiStd(newDate);
                    printf("\n");
                }
            }
        }
        else if (!strcmp(argv[1], "sick")) // sick <startcode> -- Send startcode and idcode to server
        {
            if (argc != 3)
            {
                printf("Wrong amount of arguments for 'sick' command, type 'help' for available commands");
            }
            else if (!validStartcode(atoi(argv[2])) || strlen(argv[2]) > 6) // check valid startcode and length
            {
                printf("Invalid start code, has to be exactly 6 numbers");
            }
            else
            {
                printf("Reporting own device %d to server with start code %d", yourIdCode, atoi(argv[2]));
            }
        }
        else if (!strcmp(argv[1], "check")) // check <id code> -- check if an idcode exists in the stored file
        {
            FILE *fileptr = fopen(filename, "rb");
            if (argc != 3)
            {
                printf("Wrong amount of arguments for 'check' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7) // check valid id code and length
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else if (fileptr == NULL) // either failed to open file or there is no data stored
            {
                printf("Failed to open file or no data stored on device\n");
            }
            else
            {
                // Read data from file and check if idcode exists in the heap
                heapReadFromFile(fileptr, heap);
                setToToday(&todaysDate);
                deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                idData d;
                d.idCode =  atoi(argv[2]);
                if (lookupOnSecond(heap, d))
                {
                    printf("You've been exposed to corona!");
                }
                else
                {
                    printf("Code not found, not exposed");
                }
            }
            fclose(fileptr);
        }
        else if (!strcmp(argv[1], "debug")) // debug
        {
            FILE *fileptr = fopen(filename, "rb");
            if (fileptr == NULL) // either failed to open file or there is no data stored
            {
                printf("Failed to open file or no data stored on device\n");
            }
            else
            {
                /*
                Read data from file, delete old data according to n amount of days in range set from todays date,
                sort it and then print the whole heap.
                */
                heapReadFromFile(fileptr, heap);
                setToToday(&todaysDate);
                deleteOldIdData(heap, getNDaysPrevious(todaysDate, DAYS_IN_RANGE));
                heap = heapSort(heap);
                printf("Stored data\n");
                heapPrint(heap);
            }
            fclose(fileptr);
        }
        else if (!strcmp(argv[1], "help")) // welp :(
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