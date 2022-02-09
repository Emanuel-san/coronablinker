#ifndef LISTH__
#define LISTH__
#include <stdio.h>
#include "date.h"

/**
 * @brief Datatype for storing ID data such as date and identification code.
 *
 */
typedef struct idDataStruct
{
    date date;
    int idCode;

} idData;

/**
 * @brief Struct for storing a ID list node
 *
 */
struct idNodeStruct
{
    idData data;
    struct idNodeStruct *next;
};

/**
 * @brief Datatype for one ID node in the list.
 *
 */
typedef struct idNodeStruct idNode;

/**
 * @brief Datatype for a ID list.
 *
 */
typedef idNode *idList;

/**
 * @brief Create an empty ID list.
 *
 * @returns An empty header
 */
idList createList(void);

/**
 * @brief Function to create a new ID node with ID data and insert it into the list.
 *
 * @param header The ID list the node will be insereted into.
 * @param aDate Date that will be inserted into nodes ID data.
 * @param idCode ID code that will be inserted into nodes ID data.
 */
void createNewNode(idList *header, date aDate, int idCode);

/**
 * @brief
 *
 * @param filePtr
 * @param list
 */
void listWriteToFile(FILE *filePtr, idList list);

/**
 * @brief
 *
 * @param filePtr
 * @param list
 */
idList listReadFromFile(FILE *filePtr, idList list);

/**
 * @brief Function to print everything stored in the list.
 *
 * @param header ID list to print.
 */
void printListAll(idList header);

/**
 * @brief Get the Twenty One Days Later object
 *
 * @param days
 * @return date
 */
date getTwentyOneDaysLater(int days);

/**
 * @brief Function to delete ID codes that are older then a given amount of previous days set from todays date.
 *
 * @param header ID list to remove old id codes from.
 * @param days amount of previous days.
 */
void deleteOldIdCodes(idList *header, int days);

/**
 * @brief Takes a list of IDs and frees all of its nodes in memory until its empty.
 *
 * @param header ID list to be cleared.
 */
void destroyList(idList *header);

/**
 * @brief Function to check if the list contains any nodes.
 *
 * @param header The list to check for nodes.
 * @returns true if the list contains no nodes (empty list), else false.
 */
bool listIsEmpty(idList header);
#endif