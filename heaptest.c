#include <stdio.h>
#include "date.h"
#include "heap.h"
#include "unittest.h"
#define MAX_SIZE = 100000

int main(void)
{
    idHeap heap;
    idData data;
    date aDate;
    setToToday(&aDate);
    data.date = aDate;
    data.idCode = 123456;

    TEST_CASE("Testing createHeap");
    heap = createHeap();

    TEST_CASE("Testing heapIsEmpty");
    VERIFY(heapIsEmpty(heap), "Heap is empty");

    TEST_CASE("Testing heapInsert");
    heapInsert(heap, data);
    VERIFY(!heapIsEmpty(heap), "Heap is not empty");
    printFiStd(heap->data[0].date);
    printf("\n%d", heap->data[0].idCode);
    printf("\n%d", heap->last);
}
