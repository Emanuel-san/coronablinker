#ifndef HEAP__
#define HEAP__

#include <stdio.h>
#include "date.h"
#include "devicepair.h"

/**
 * @brief Struct for storing a heap of idData structs
*/
struct idHeapStruct
{
    int currentSize; // To keep track of the current size of the heap.
    int last;        // Keep track of the last element in the heap
    idData data[];   // data array e.g [{idData, idData, ....}]
};

/**
 * @brief Datatype for a ID heap
 */
typedef struct idHeapStruct *idHeap;

/**
 * @brief Create a Heap object
 * @returns An empty heap with allocated memory
 */
idHeap createHeap(void);

/**
 * @brief Function for checking if a heap is empty
 * @param heap The heap to check if empty
 * @returns true if heap is empty, false otherwise
 */
bool heapIsEmpty(idHeap heap);

/**
 * @brief Function for inserting an idData element into the heap
 * @param heap The heap to insert the idData element into
 * @param data The idData element to insert
 * @returns The heap (the new heap if resizing is needed)
 */
idHeap heapInsert(idHeap heap, idData data);

/**
 * @brief Function for removing the idData element with the oldest date in the heap
 * @param heap The heap from which to remove the element
 * @return The idData element that is removed
 */
idData heapPop(idHeap heap);

/**
 * @brief Function for printing the elements in the heap
 * @param heap The heap to be printed
 */
void heapPrint(idHeap heap);

/**
 * @brief Function for sorting the heap to easily print in correct order
 * @param heap The heap to be sorted
 * @return The sorted heap
 */
idHeap heapSort(idHeap heap);

/**
 * @brief Function for deleting elements older than a specific cutoff date
 * @param heap The heap from which to remove the old elements
 * @param cutoff The cutoff date
 */
void deleteOldIdData(idHeap heap, date cutoff);

/**
 * @brief Function for searching for a data element in a heap based on its second key
 * @param heap The heap to search
 * @param lookup An idData element with the second key we're looking for
 * @returns True if the  is in the heap, false otherwise
 */
bool lookupOnSecond(idHeap heap, idData lookup);

/**
 * @brief Function for destroying a heap
 * @param heap The heap to destroy
 * @returns NULL if the heap is destroyed, the heap otherwise
 */
idHeap heapDestroy(idHeap heap);

/**
 * @brief Function for writing the elements of the heap to a file
 * @param filePtr A pointer to the file to write to
 * @param heap The heap to write to the file
 */
void heapWriteToFile(FILE *filePtr, idHeap heap);

/**
 * @brief Function for reading from a file to a heap
 * @param filePtr A pointer to the file to read from
 * @param heap The heap to read into
 * @returns The heap (the new heap if resizing is needed)
 */
idHeap heapReadFromFile(FILE *filePtr, idHeap heap);

/**
 * @brief Function for creating a idData element
 * @param newDate The date to put in the idData element
 * @param newIdCode The idCode to put in the idData element
 * @return The new idData element
 */
idData createIdDataElement(date newDate, int newIdCode);

/**
 * @brief Function for resizing the heap if the total number of elements is reached
 * @param heap A pointer to the original heap
 * @returns The pointer to the new bigger heap
 */
idHeap heapResize(idHeap heap);

#endif