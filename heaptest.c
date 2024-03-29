#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input.h"
#include "date.h"
#include "heap.h"
#include "unittest.h"
#define MAX_SIZE = 100000

bool heapCheckTestSort(idHeap heap)
{

    bool sortCheck = true;

    for (int i = 0; i < heap->last && sortCheck == true; i++)
    {
        // printf("%d", i);
        sortCheck = isBefore(heap->data[i].date, heap->data[i + 1].date);
    }
    return sortCheck;
}

void createTestHeap(idHeap heap)
{
    date aDate;
    idData inData;
    inData.idCode = 1234563;

    setDate(&aDate, 12, 2, 2022);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 5, 1, 2022);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 28, 12, 2021);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 20, 2, 2022);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 20, 3, 2022);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 10, 3, 2022);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 4, 11, 2021);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 21, 10, 2021);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 5, 5, 2022);
    inData.idCode = 6475656;
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 7, 8, 2019);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 20, 9, 2023);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
    setDate(&aDate, 10, 10, 2020);
    inData.date = aDate;
    heap = heapInsert(heap, inData);
}

int main(int argc, char *argv[])
{

    idHeap heap = NULL, heap2, heap3;
    idData inData, outData;
    date aDate;
    setToToday(&aDate);
    inData.date = aDate;
    inData.idCode = 123456;
    char *filename = "IDCodesbinary.txt";
    int yourIdCode = 9999999;

    if (argc == 1)
    {
        TEST_CASE("Testing createHeap");
        heap = createHeap();
        heap2 = createHeap();
        heap3 = createHeap();
        int initialSize = heap->currentSize;

        TEST_CASE("Testing heapResize");
        VERIFY(heap->currentSize == initialSize, "The heap is still at starting size ");
        printf("%d\n", initialSize);
        heap = heapResize(heap);
        VERIFY(heap->currentSize > initialSize, "The heap size has increased from starting size and is now ");
        printf("%d\n", heap->currentSize);

        initialSize = heap3->currentSize;
        TEST_CASE("Testing that heapInsert reallocs(heapResize) when needed");
        VERIFY(heap3->currentSize == initialSize, "The heap is still at starting size ");
        printf("%d\n", initialSize);

        setDate(&aDate, 5, 5, 2022);
        inData.idCode = 6475656;
        inData.date = aDate;
        int current = heap3->currentSize;
        for (int i = 0; i < current + 3; i++)
        {
            heap3 = heapInsert(heap3, inData);
        }
        VERIFY(heap3->currentSize > initialSize, "The heap size has increased from starting size and is now ");
        printf("%d\n", heap3->currentSize);

        TEST_CASE("Testing heapIsEmpty");
        VERIFY(heapIsEmpty(heap), "Heap is empty");

        TEST_CASE("Testing heapInsert");
        heap = heapInsert(heap, inData);
        VERIFY(!heapIsEmpty(heap), "Heap is not empty");
        printf("Root data in heap is now\n");
        printFiStd(heap->data[0].date);
        printf("\n%d", heap->data[0].idCode);
        printf("\n%d", heap->last);

        TEST_CASE("testing heapPrint");
        heapPrint(heap);

        TEST_CASE("Testing heapPop");
        outData = heapPop(heap);
        VERIFY(heapIsEmpty(heap), "Heap is empty");
        printf("Out data from heapPop\n");
        printFiStd(outData.date);
        printf("\n%d", outData.idCode);
        printf("\n%d", heap->last);

        TEST_CASE("Testing sortHeap");
        createTestHeap(heap);
        VERIFY(!heapCheckTestSort(heap), "Heap is not sorted");
        heapPrint(heap);
        printf("\n");
        heap = heapSort(heap);
        VERIFY(heapCheckTestSort(heap), "Heap is sorted");
        heapPrint(heap);

        TEST_CASE("Testing deleteOldIdCode");
        setDate(&aDate, 31, 12, 2021);
        deleteOldIdData(heap, aDate);
        VERIFY(!isBefore(heap->data[0].date, aDate), "All dates older then 31.12.2021 is deleted");
        heap = heapSort(heap);
        heapPrint(heap);

        TEST_CASE("testing isIdCodeInHeap");
        VERIFY(isIdCodeinHeap(heap, 6475656), "Id code is in heap");
        VERIFY(!isIdCodeinHeap(heap, 9999999), "Id code is not in heap");

        TEST_CASE("Testing binary write and read from files");
        FILE *fileptr = fopen(filename, "wb");
        heapWriteToFile(fileptr, heap);
        fclose(fileptr);

        fileptr = fopen(filename, "rb");
        heapReadFromFile(fileptr, heap2);
        fclose(fileptr);
        VERIFY(heap2->last == heap->last, "Both heaps have the same number of data elements after write and read");

        TEST_CASE("Testing heapDestroy");
        VERIFY(heap2 != NULL, "Heap is not null");
        heap2 = heapDestroy(heap2);
        VERIFY(heap2 == NULL, "Heap is null");
    }
    else
    {
        heap = createHeap();
        heap2 = createHeap();
        // char *command_strings[] = {"add", "sick", "check", "debug", "help"};
        // printf("%d", atoi(argv[2]));
        if (!strcmp(argv[1], "add")) // strcmp returns 0 if strings are equal
        {
            if (argc != 4)
            {
                printf("Wrong amount of arguments for 'sick' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7)
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else
            {
                int day, month, year;
                char *delimiters = "./-";
                date newDate;
                day = atoi(strtok(argv[3], delimiters));
                month = atoi(strtok(NULL, delimiters));
                year = atoi(strtok(NULL, delimiters));
                setDate(&newDate, day, month, year);
                if (!checkDate(newDate) || isDateInFuture(newDate))
                {
                    printf("Invalid date!");
                }
                else
                {
                    FILE *fileptr = fopen(filename, "rb");
                    heapReadFromFile(fileptr, heap2);
                    fclose(fileptr);

                    heap2 = heapInsert(heap2, createIdDataElement(newDate, atoi(argv[2])));
                    setDate(&aDate, 31, 12, 2021);
                    deleteOldIdData(heap2, aDate);
                    fileptr = fopen(filename, "wb");
                    heapWriteToFile(fileptr, heap2);
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
            if (argc != 3)
            {
                printf("Wrong amount of arguments for 'check' command, type 'help' for available commands");
            }
            else if (!validIdcode(atoi(argv[2])) || strlen(argv[2]) > 7)
            {
                printf("Invalid ID code, has to be exactly 7 numbers");
            }
            else
            {
                FILE *fileptr = fopen(filename, "rb");
                heapReadFromFile(fileptr, heap2);
                fclose(fileptr);
                setDate(&aDate, 31, 12, 2021);
                deleteOldIdData(heap2, aDate);
                // heapPrint(heap2);
                if (isIdCodeinHeap(heap2, atoi(argv[2])))
                {
                    printf("You've been exposed to corona!");
                }
            }
        }
        else if (!strcmp(argv[1], "debug"))
        {
            FILE *fileptr = fopen(filename, "rb");
            heapReadFromFile(fileptr, heap2);
            fclose(fileptr);
            setDate(&aDate, 31, 12, 2021);
            deleteOldIdData(heap2, aDate);
            printf("Stored data\n");
            heapPrint(heap2);
        }
        else if (!strcmp(argv[1], "help"))
        {
        }
        else
        {
            printf("Unkown argument, type 'help' for available commands");
        }
    }
}