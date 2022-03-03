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
struct idNodeStruct
{
    idData data[100000];
    int last;
};

typedef struct idNodeStruct *idNode;

#endif