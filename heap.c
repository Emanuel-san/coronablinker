#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "heap.h"

idHeap createHeap(void)
{
    idHeap tmp = malloc(sizeof(struct idHeapStruct));
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

    // Set the new data furthest down in the "tree" (last + 1) and set child as that node
    heap->data[++(heap->last)] = data;
    child = heap->last;

    // Loop while the new node still havent wandered up to the root.
    while (child != 0)
    {
        // Find the parent node of the child node
        parent = (child - 1) / 2;

        // Child and parent will swap places if the childs date in data is before the date of the parent.
        if (isBefore(heap->data[child].date, heap->data[parent].date))
        {
            tmp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        else
        {
            // Break out of the loop is the child is now in the correct spot in the heap
            break;
        }

        // Move the child up one level and check again.
        child = parent;
    }
}

idData heapPop(idHeap heap)
{
    int parent, child;

    idData tmp, oldestData;

    if (heap == NULL)
    {
        printf("Heap has no allocated memory, exiting.");
        exit(EXIT_FAILURE);
    }
    if (heap->last <= -1)
    {
        printf("Exited heapPop with an empty heap, error was not caught earlier, exiting");
        exit(EXIT_FAILURE);
    }

    /* When root is removed it has to replaced by the last node in the heap "tree" */
    oldestData = heap->data[0];               // data we return from function
    heap->data[0] = heap->data[(heap->last)]; // move last node to root
    heap->last--;
    parent = 0;

    // As we move the node down the tree we make sure we done go past the current size(heap->last) of the heap.
    // If the parent is bigger or equal to the size then we are at the bottom and should not move further
    while (parent * 2 + 1 <= heap->last)
    {

        child = 2 * parent + 1;

        // Compare the tweo child nodes and choose the oldest one to ensure we always change with the oldest date if needed
        if (isBefore(heap->data[child + 1].date, heap->data[child].date))
        {
            child++;
        }

        // If the child is older then the parent then we change
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

idHeap heapDestroy(idHeap heap)
{
    if (heap == NULL)
    {
        printf("ERROR!\n");
        return heap;
    }
    free(heap);
    heap = NULL;
    return heap;
}

void heapWriteToFile(FILE *filePtr, idHeap heap)
{

    /*for (int i = 0; i <= heap->last; i++)
    {
        fprintf(filePtr, "id: %d date: %d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }*/
    fwrite(heap->data, sizeof(idData), heap->last + 1, filePtr);
}

void heapReadFromFile(FILE *filePtr, idHeap heap)
{
    // idData data;
    // while (fscanf(filePtr, "id: %d date: %d.%d.%d\n", &data.idCode, &data.date.day, &data.date.month, &data.date.year) == 4)
    // {
    //     heapInsert(heap, data);
    // }
    idData data;
    while (fread(&data, sizeof(idData), 1, filePtr) == 1)
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