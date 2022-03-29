#ifndef DEVICEPAIR_H
#define DEVICEPAIR_H
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
 * @brief Compares two pairs and matches the second value.
 * 
 * @param d1 first pair to compare
 * @param d2 second pair to compare
 * @return true if equal
 * @return false otherwise
 */
bool compareSecond (idData d1, idData d2);
#endif