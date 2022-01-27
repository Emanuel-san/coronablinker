#include "list.h"
#include <stdlib.h>
#include <stdio.h>

idList createList(void)
{
    return NULL;
}

void createNewNode(idList *header, date aDate, int idCode)
{
    idNode *newNode;
    newNode = (idNode *)malloc(sizeof(idNode));
    if (newNode == NULL)
    {
        printf("FAIL! Memory alocation failed!\n");
        return;
    }
    newNode->data.date = aDate;
    newNode->data.idCode = idCode;
    if (*header == NULL)
    {
        *header = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = *header;
        *header = newNode;
    }
}