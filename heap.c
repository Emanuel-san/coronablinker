#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "heap.h"

idHeap createHeap(void)
{
    idHeap tmp = (idHeap)malloc(sizeof(struct idHeapStruct));
    /* Vi utgår här från att endast positiva prioriteter > 0 förekommer */
    // memset(tmp->data, 0, MAX_SIZE * sizeof(int));
    if (tmp == NULL)
    {
        printf("Memory allocation failed. Exiting");
        exit(0);
    }
    tmp->last = -1;
    return tmp;
}

bool heapIsEmpty(idHeap heap)
{
    return (heap->last == -1);
}

void heapInsert(idHeap heap, idData data)
{
    int parent, child;
    idData tmp;

    if (heap == NULL)
    {
        printf("ERROR!\n");
        return;
    }

    // TODO FIXA REALLOC
    if (heap->last == 99999)
    {
        // printf("GO HOME! You reached the end of the heap!\n");
        return;
    }

    /* Börja med att lägga det nya värdet som en ny nod sist i trädet */
    heap->data[++(heap->last)] = data;
    child = heap->last;

    /* Det nya värdet kan vandra hela vägen upp till roten */
    while (child != 0)
    {

        parent = (child - 1) / 2; // avrundar nedåt med heltalsdivision

        /* Låt föräldern och barnet byta plats om det behövs */
        if (isBefore(heap->data[child].date, heap->data[parent].date))
        {
            tmp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        else
        {
            /* Nu har vi lyft noden till rätt nivå i trädet */
            break;
        }

        /* Gå upp en nivå och upprepa */
        child = parent;
    }
}

idData heapPop(idHeap heap)
{
    int parent, child;

    idData tmp, oldestData;

    if (heap == NULL)
    {
        printf("ERROR!\n");
        return oldestData;
    }
    if (heap->last <= -1)
    {
        // printf("Can't delete, heap is empty\n");
        return oldestData;
    }

    /* Tas roten bort skall den ersättas med den sista noden i trädet... */
    oldestData = heap->data[0];
    heap->data[0] = heap->data[(heap->last)];
    heap->last--;
    parent = 0;

    /* ...som sedan vandrar nedåt tills den funnit sin rätta plats igen */
    while (parent * 2 + 1 <= heap->last)
    {

        child = 2 * parent + 1;

        /* Ett potentiellt byte sker alltid med det större barnet */
        if (isBefore(heap->data[child + 1].date, heap->data[child].date))
        {
            child++;
        }

        /* Låt föräldern och barnet byta plats om det behövs */
        if (isBefore(heap->data[child].date, heap->data[parent].date))
        {
            tmp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        else
        {
            /* Nu har vi sänkt noden till rätt nivå i trädet */
            break;
        }

        /* Gå ner en nivå och upprepa */
        parent = child;
    }

    return oldestData;
}

idHeap heapSort(idHeap heap)
{

    if (heap->last <= -1)
    {
        // printf("Can't sort, heap is empty\n");
        return heap;
    }

    idHeap sortedHeap = createHeap();

    while (heap->last > -1)
    {
        heapInsert(sortedHeap, heapPop(heap));
    }

    free(heap);
    return sortedHeap;
}

void heapPrint(idHeap heap)
{

    for (int i = 0; i <= heap->last; i++)
    {
        printf("id: %d date: %d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }
}

void deleteOldIdData(idHeap heap, date cutoff)
{
    if (heap->last <= -1)
    {
        // printf("Can't delete, heap is empty\n");
        return;
    }
    while (isBefore(heap->data[0].date, cutoff) && heap->last > -1)
    {
        heapPop(heap);
    }
}

bool isIdCodeinHeap(idHeap heap, int code)
{
    for (int i = 0; i <= heap->last; i++)
    {
        if (heap->data[i].idCode == code)
        {
            return true;
        }
    }
    return false;
}

void heapDestroy(idHeap heap)
{
    if (heap == NULL)
    {
        printf("ERROR!\n");
        return;
    }
    free(heap);
}

void heapWriteToFile(FILE *filePtr, idHeap heap)
{

    for (int i = 0; i <= heap->last; i++)
    {
        fprintf(filePtr, "id: %d date: %d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }
}

void heapReadFromFile(FILE *filePtr, idHeap heap)
{
    idData data;
    while (fscanf(filePtr, "id: %d date: %d.%d.%d\n", &data.idCode, &data.date.day, &data.date.month, &data.date.year) == 4)
    {
        heapInsert(heap, data);
    }
}

idData createIdDataElement(date newDate, int newIdCode)
{
    idData newIdData;
    newIdData.date = newDate;
    newIdData.idCode = newIdCode;
    return newIdData;
}