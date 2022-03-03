#ifndef LISTH__
#define LISTH__
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
    idData data;
    struct idNodeStruct *next;
};

/**
 * @brief Datatype for one ID node in the list.
 */
typedef struct idNodeStruct idNode;

/**
 * @brief Datatype for a ID list.
 */
typedef idNode *idList;

/**
 * @brief Create an empty ID list.
 * @returns An empty header
 */
idList createList(void);

/**
 * @brief Function to create a new ID node with ID data and insert it into the list.
 * @param header The ID list the node will be insereted into.
 * @param aDate Date that will be inserted into nodes ID data.
 * @param idCode ID code that will be inserted into nodes ID data.
 */
void createNewNode(idList *header, date aDate, int idCode);

/**
 * @brief Function for writing content of list to a file
 * @param filePtr Pointer to the file to write to
 * @param list The list to be written to the list
 */
void listWriteToFile(FILE *filePtr, idList list);

/**
 * @brief Function fpr reading from file
 * @param filePtr Pointer to the file to be read from
 * @param list The list in which to save the content of the file
 * @returns The new list with the same content as the file
 */
idList listReadFromFile(FILE *filePtr, idList list);

/**
 * @brief Function to print everything stored in the list.
 * @param header ID list to print.
 */
void printListAll(idList header);

/**
 * @brief Function to delete ID codes that are older then a given amount of previous days set from todays date.
 * @param header ID list to remove old id codes from.
 * @param days amount of previous days.
 */
void deleteOldIdCodes(idList *header, date cutoff);

/**
 * @brief Takes a list of IDs and frees all of its nodes in memory until its empty.
 * @param header ID list to be cleared.
 */
void destroyList(idList *header);

/**
 * @brief Function to check if the list contains any nodes.
 * @param header The list to check for nodes.
 * @returns true if the list contains no nodes (empty list), else false.
 */
bool listIsEmpty(idList header);

/**
 * @brief Function for checking if an Idcode is in the list
 * @param header The list to check
 * @param idCode The IDcode to look for
 * @returns true if IdCode is in the list, false otherwise
 */
bool isCodeInList(idList header, int idCode);

/**
 * @brief Function for checking if a date is in the list
 * @param header The list to check
 * @param idCode The date to look for
 * @returns true if date is in the list, false otherwise
 */
bool isDateInList(idList header, date date);
#endif