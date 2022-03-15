#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "heap.h"

idHeap createHeap(void)
{
    int startsize = 40;

    idHeap tmp = malloc(sizeof(struct idHeapStruct) + startsize * sizeof(idData));
    // memset(tmp->data, 0, MAX_SIZE * sizeof(int));
    if (tmp == NULL)
    {
        printf("Memory allocation failed. Exiting");
        exit(0);
    }
    tmp->last = -1;
    tmp->currentSize = startsize;
    return tmp;
}

bool heapIsEmpty(idHeap heap)
{
    return (heap->last == -1);
}

idHeap heapInsert(idHeap heap, idData data)
{
    int parent, child;
    /*
         PARENT
         /   \
        /     \
     CHILD   CHILD

    */

    idData tmp;

    if (heap == NULL)
    {
        printf("Heap has no allocated memory, exiting.\n");
        exit(EXIT_FAILURE);
    }

    if (heap->last == heap->currentSize - 1) // If we've reached the currently allocated max size then we reallocate more memory for the heap before we insert again.

    {
        heap = heapResize(heap);
    }

    heap->data[++(heap->last)] = data; // Set the new data furthest down in the "tree" (last + 1) and set child as that node

    child = heap->last;

    while (child != 0) // Loop while the new node still havent wandered up to the root.

    {
        parent = (child - 1) / 2; // Find the parent node of the child node

        if (isBefore(heap->data[child].date, heap->data[parent].date)) // Child and parent will swap places if the childs date in data is before the date of the parent.

        {
            tmp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        else
        {
            break; // Break out of the loop if the child is now in the correct spot in the heap
        }

        child = parent; // Move the child up one level and check again.
    }
    return heap;
}

idData heapPop(idHeap heap)
{
    int parent, child;
    /*
         PARENT
         /   \
        /     \
     CHILD   CHILD

    */

    idData tmp, oldestData; // tmp is used to move a node if needed

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
    heap->last--;                             // increment back our index since we're removing an element
    parent = 0;

    /*  As we move the node down the tree we make sure we don't go past the current size(heap->last) of the heap.
        If the parent is bigger or equal to the size then we are at the bottom and should not move further */
    while (parent * 2 + 1 <= heap->last)
    {

        child = 2 * parent + 1;

        if (isBefore(heap->data[child + 1].date, heap->data[child].date)) // Compare the tweo child nodes and choose the oldest one to ensure we always change with the oldest date if needed

        {
            child++;
        }

        if (isBefore(heap->data[child].date, heap->data[parent].date)) // If the child is older then the parent then we change

        {
            tmp = heap->data[child];
            heap->data[child] = heap->data[parent];
            heap->data[parent] = tmp;
        }
        else
        {
            break; // The node is now at the right spot and we break out of the loop
        }

        parent = child; // Move the node down one level in the tree and repeat the check
    }

    return oldestData;
}

idHeap heapSort(idHeap heap)
{

    if (heap->last <= -1) // heap is empty
    {
        return heap;
    }

    idHeap sortedHeap = createHeap();

    while (heap->last > -1)
    {
        sortedHeap = heapInsert(sortedHeap, heapPop(heap)); // Insert poped nodes into the temporary heap
    }

    free(heap); // frre memory of the old heap
    return sortedHeap;
}

void heapPrint(idHeap heap)
{

    for (int i = 0; i <= heap->last; i++) // print data untill we get to the last element
    {
        printf("id: %d date: %d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }
}

void deleteOldIdData(idHeap heap, date cutoff)
{
    if (heap->last <= -1) // empty heap
    {
        return;
    }
    while (isBefore(heap->data[0].date, cutoff) && heap->last > -1) // Pop untill the root becomes the same or a later date then our cutoff date.
    {
        heapPop(heap);
    }
}

bool isIdCodeinHeap(idHeap heap, int code)
{
    for (int i = 0; i <= heap->last; i++) // loop untill we reach the last element...
    {
        if (heap->data[i].idCode == code) // ...or we find the ID code in the heap
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
    free(heap);  // free the allocated memory for the heap...
    heap = NULL; //.. and set it to NULL
    return heap;
}

void heapWriteToFile(FILE *filePtr, idHeap heap)
{

    /*for (int i = 0; i <= heap->last; i++)
    {
        fprintf(filePtr, "id: %d date: %d.%d.%d\n", heap->data[i].idCode, heap->data[i].date.day, heap->data[i].date.month, heap->data[i].date.year);
    }*/

    fwrite(heap->data, sizeof(idData), heap->last + 1, filePtr); // BINARY STORAGE
}

idHeap heapReadFromFile(FILE *filePtr, idHeap heap)
{
    // idData data;
    // while (fscanf(filePtr, "id: %d date: %d.%d.%d\n", &data.idCode, &data.date.day, &data.date.month, &data.date.year) == 4)
    // {
    //     heapInsert(heap, data);
    // }

    idData data;
    while (fread(&data, sizeof(idData), 1, filePtr) == 1) // BINARY READ -- read untill fread dosen't get a succesfull "read"
    {
        heap = heapInsert(heap, data);
    }
    return heap;
}

idData createIdDataElement(date newDate, int newIdCode)
{
    idData newIdData;
    newIdData.date = newDate;
    newIdData.idCode = newIdCode;
    return newIdData;
}

idHeap heapResize(idHeap heap)
{
    heap = realloc(heap, sizeof(struct idHeapStruct) + (heap->currentSize + 40) * sizeof(idData)); // add another 40 idData to heap.

    // increase currentSize to keep track of the heap size.
    heap->currentSize += 40;
    return heap;
}
