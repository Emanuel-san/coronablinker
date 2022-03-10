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
    heapInsert(heap, inData);
    setDate(&aDate, 5, 1, 2022);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 28, 12, 2021);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 20, 2, 2022);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 20, 3, 2022);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 10, 3, 2022);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 4, 11, 2021);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 21, 10, 2021);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 5, 5, 2022);
    inData.idCode = 6475656;
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 7, 8, 2019);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 20, 9, 2023);
    inData.date = aDate;
    heapInsert(heap, inData);
    setDate(&aDate, 10, 10, 2020);
    inData.date = aDate;
    heapInsert(heap, inData);
}

int main(int argc, char *argv[])
{

    idHeap heap = NULL, heap2;
    idData inData, outData;
    date aDate;
    setToToday(&aDate);
    inData.date = aDate;
    inData.idCode = 123456;
    char *filename = "IDCodesbinary.txt";

    // TEST_CASE("Testing createHeap");
    heap = createHeap();
    heap2 = createHeap();

    if (argc == 1)
    {

        TEST_CASE("Testing heapIsEmpty");
        VERIFY(heapIsEmpty(heap), "Heap is empty");

        TEST_CASE("Testing heapInsert");
        heapInsert(heap, inData);
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

        TEST_CASE("Testing heapPop and heapSort on empty heap");
        heapPop(heap);
        heap = heapSort(heap);

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

        TEST_CASE("Testing binary write");
        FILE *fileptr = fopen(filename, "wb");
        heapWriteToFile(fileptr, heap);
        fclose(fileptr);

        TEST_CASE("Testing binary read");
        fileptr = fopen(filename, "rb");
        heapReadFromFile(fileptr, heap2);
        fclose(fileptr);
        heapPrint(heap2);
    }

    // char *command_strings[] = {"add", "sick", "check", "debug", "help"};
    // printf("%d", atoi(argv[2]));
    if (!strcmp(argv[1], "add")) // strcmp returns 0 if strings are equal
    {
    }
    else if (!strcmp(argv[1], "sick"))
    {
    }
    else if (!strcmp(argv[1], "check"))
    {
        if (argc != 3)
        {
            printf("Wrong amount of arguments for 'check' command, type 'help' for available commands");
        }
        else if (!validIdcode(atoi(argv[2])))
        {
            printf("Invalid ID code, has to be exactly 7 numbers");
        }
        else
        {
            FILE *fileptr = fopen(filename, "rb");
            heapReadFromFile(fileptr, heap2);
            fclose(fileptr);
            setDate(&aDate, 31, 12, 2021);
            deleteOldIdData(heap, aDate);
            // heapPrint(heap2);
            if (isIdCodeinHeap(heap2, atoi(argv[2])))
            {
                printf("You've been exposed to corona!");
            }
        }
    }
    else if (!strcmp(argv[1], "debug"))
    {
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