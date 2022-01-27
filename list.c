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

void printListAll(idList header)
{
    idNode *currentNode = header;

    while (currentNode != NULL)
    {
        printFiStd(currentNode->data.date);
        printf(" ID: %d\n", currentNode->data.idCode);
        currentNode = currentNode->next;
    }
}

void deleteOldIdCodes(idList *header, int days)
{
    idNode *currentNode = *header;
    idNode *previousNode = NULL;
    date today, nDaysPrevious;
    setToToday(&today);
    nDaysPrevious = getNDaysPrevious(today, days);

    while (currentNode != NULL)
    {
        if (isBefore(currentNode->data.date, nDaysPrevious))
        {
            if (previousNode == NULL)
            {
                *header=currentNode->next;
                free(currentNode);
                currentNode=*header;
            }
            else{
                previousNode->next=currentNode->next;
                free(currentNode);
                currentNode=previousNode->next;
            }

        }
        else{
            previousNode=currentNode;
            currentNode=currentNode->next;
        }
    }
}