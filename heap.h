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
 * @brief Struct for storing a ID list node
 */
struct idHeapStruct
{
    idData data[100000];
    int last;
};

/**
 * @brief
 */
typedef struct idHeapStruct *idHeap;

/**
 * @brief Create a Heap object
 */
idHeap createHeap(void);

/**
 * @brief
 */
bool heapIsEmpty(idHeap heap);

/**
 * @brief
 */
void heapInsert(idHeap heap, idData data);

/**
 * @brief
 *
 * @param p
 * @return int
 */
idData heapDelete(idHeap heap);

#endif