#include <stdio.h>
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
    inData.idCode = 123456;

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
    inData.idCode = 647565;
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

int main(void)
{
    idHeap heap = NULL, heap2;
    idData inData, outData;
    date aDate;
    setToToday(&aDate);
    inData.date = aDate;
    inData.idCode = 123456;

    TEST_CASE("Testing createHeap");
    heap = createHeap();
    heap2 = createHeap();

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
    VERIFY(isIdCodeinHeap(heap, 647565), "Id code is in heap");
    VERIFY(!isIdCodeinHeap(heap, 999999), "Id code is not in heap");

    TEST_CASE("Testing binary write");
    char *filename = "IDCodesbinary.txt";
    FILE *fileptr = fopen(filename, "wb");
    heapWriteToFile(fileptr, heap);
    fclose(fileptr);

    TEST_CASE("Testing binary read");
    fileptr = fopen(filename, "rb");
    heapReadFromFile(fileptr, heap2);
    fclose(fileptr);
    heapPrint(heap2);
}