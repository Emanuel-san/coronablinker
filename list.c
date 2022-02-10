#include "list.h"
#include "date.h"
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
    if (*header == NULL) // empty list
    {
        *header = newNode;
        newNode->next = NULL;
    }
    else // insert new node as header
    {
        newNode->next = *header;
        *header = newNode;
    }
}

void listWriteToFile(FILE *filePtr, idList list)
{

    idNode *currentNode = list;

    while (currentNode != NULL)
    {

        fprintf(filePtr, "id: %d date: %d.%d.%d\n", currentNode->data.idCode, currentNode->data.date.day, currentNode->data.date.month, currentNode->data.date.year);
        currentNode = currentNode->next;
    }
}

idList listReadFromFile(FILE *filePtr, idList list)
{
    date newDate;
    int idCode, fieldsRead = 0;

    do
    {
        fieldsRead = fscanf(filePtr, "id: %d date: %d.%d.%d\n", &idCode, &newDate.day, &newDate.month, &newDate.year);
        if (fieldsRead == 4)
        {
            createNewNode(&list, newDate, idCode);
        }
    } while (fieldsRead == 4);

    return list;
}

void printListAll(idList header)
{
    idNode *currentNode = header;
    printf("**********************\n");
    if (listIsEmpty(header))
    {
        printf("List is empty\n");
    }
    while (currentNode != NULL)
    {
        printFiStd(currentNode->data.date);
        printf(" ID: %d\n", currentNode->data.idCode);
        currentNode = currentNode->next;
    }
    printf("**********************\n");
}

date getTwentyOneDaysLater(int days)
{
    date today;
    setToToday(&today);
    return getNDaysPrevious(today, days);
}

void deleteOldIdCodes(idList *header, int days)
{
    idNode *currentNode = *header;
    idNode *previousNode = NULL;
    date nDaysPrevious;
    // date today, nDaysPrevious;
    // setToToday(&today);
    // nDaysPrevious = getNDaysPrevious(today, days);
    nDaysPrevious = getTwentyOneDaysLater(days);

    while (currentNode != NULL)
    {
        if (isBefore(currentNode->data.date, nDaysPrevious)) // if node date is before the given date
        {
            if (previousNode == NULL) // if there's no previous node, move header to the next node and free currentNode.
            {
                *header = currentNode->next;
                free(currentNode);
                currentNode = *header;
            }
            else // else set previous nodes next pointer to jump over currentNode and free currentNode.
            {
                previousNode->next = currentNode->next;
                free(currentNode);
                currentNode = previousNode->next;
            }
        }
        else // iterate both nodes forward
        {
            previousNode = currentNode;
            currentNode = currentNode->next;
        }
    }
}

void destroyList(idList *header)
{
    idNode *currentNode = *header;

    while (currentNode != NULL)
    {
        *header = currentNode->next;
        free(currentNode);
        currentNode = *header;
    }
}

bool listIsEmpty(idList header)
{
    return (header == NULL);
}

bool isCodeInList(idList header, int idCode){
    idNode *currentNode = header;
    while(currentNode!=NULL){
        if(currentNode->data.idCode==idCode){
            return true;
        }
        else{
            currentNode=currentNode->next;
        }
    }
    return false;
}