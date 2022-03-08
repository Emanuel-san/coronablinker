#ifndef HEAP__
#define HEAP__

#include <stdio.h>
#include "date.h"

/**
 * @brief Datatype for storing ID data such as date and identification code.
 */
typedef struct idDataStruct
{
    date date;
    int idCode;

} idData;

/**
 * @brief Struct for storing a heap of idData structs
 */
struct idHeapStruct
{
    idData data[100000];
    int last;
};

/**
 * @brief Datatype for a ID heap
 */
typedef struct idHeapStruct *idHeap;

/**
 * @brief Create a Heap object
 * @returns An empty heap for idDates
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
 */
void heapInsert(idHeap heap, idData data);

/**
 * @brief Function for removing the idData element with the oldest date in the heap
 * @param heap The heap from which to remove the element
 * @return The idData element that is removed
 */
idData heapPop(idHeap heap);

/**
 * @brief
 *
 */
void heapPrint(idHeap heap);

/**
 * @brief
 *
 * @param heap
 * @return idHeap
 */
idHeap heapSort(idHeap heap);

#endif