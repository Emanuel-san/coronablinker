#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "heap.h"

idHeap createHeap(void)
{
    idHeap tmp = (idHeap)malloc(sizeof(struct idHeapStruct));
    /* Vi utgår här från att endast positiva prioriteter > 0 förekommer */
    // memset(tmp->data, 0, MAX_SIZE * sizeof(int));
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
        printf("GO HOME! You reached the end of the heap!\n");
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
        return;
    }
    if (heap->last <= -1)
    {
        printf("Can't delete, heap is empty\n");
        return;
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
        if (isBefore(heap->data[child + 1].date, heap->data[child].date) && heap->data[child + 1].date.day != 0)
        {
            child++;
        }

        /* Låt föräldern och barnet byta plats om det behövs */
        if (isBefore(heap->data[child].date, heap->data[parent].date) && heap->data[child].date.day != 0)
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
        printf("Can't sort, heap is empty\n");
        return;
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
        printf("ID:%d DATE:%d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }
}