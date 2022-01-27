#ifndef LISTH__
#define LISTH__

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

// TODO DOX
void createNewNode(idList *header, date aDate, int idCode);

// TODO dox
void printListAll(idList header);

// TODO dox
void deleteOldIdCodes(idList *header, int days);

idList tempListTest(idList header);
#endif