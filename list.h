#ifndef LISTH__
#define LISTH__

#include "date.h"


typedef struct idDataStruct
{
    date date;
    int idCode;

} idData;

struct idNodeStruct
{
    idData data;
    struct idNodeStruct *next;
};

typedef struct idNodeStruct idNode;

typedef idNode *idList;

//TODO dox
idList createList(void);

//TODO DOX
void createNewNode(idList* header, date aDate, int idCode);

#endif