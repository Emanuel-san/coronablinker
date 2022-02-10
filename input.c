#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

#ifdef DEBUGON
#define DEBUG(msg) printf("DEBUG %s\n", msg)
#else
#define DEBUG(msg)
#endif

// TODO change return type if necessary
void enterStartCode(int *startcode)
{

    do
    {
        printf("Please enter your start code (0 to go back): ");
        char term;
        if (scanf("%d%c", startcode, &term) != 2 || term != '\n')
        {
            printf("Invalid input.\n");
            fflush(stdin);
            *startcode = 1;
        }
        else if (*startcode == 0)
        {
            return;
        }
        else if (!validStartcode(*startcode))
        {
            printf("Invalid startcode.\n");
        }

    } while (!validStartcode(*startcode));

    printf("**********************\nSending ID- and startcode to server.\n");
}

//  TODO change return type if necessary
void enterIdCode(int *idCode)
{
    do
    {
        printf("Please enter ID code (0 to go back): ");
        char term;
        if (scanf("%d%c", idCode, &term) != 2 || term != '\n')
        {
            printf("Invalid input.\n");
            fflush(stdin);
            *idCode = 1;
        }
        else if (*idCode == 0)
        {
            return;
        }
        else if (!validIdcode(*idCode))
        {
            printf("Invalid idcode.\n");
        }
    } while (!validIdcode(*idCode));
    printf("ID code accepted!\n");
}

date enterDate(void)
{
    date newDate;
    do
    {
        printf("Enter date (DD.MM.YYYY): ");
        char term;
        if (scanf("%d.%d.%d%c", &newDate.day, &newDate.month, &newDate.year, &term) != 4 || term != '\n')
        {
            printf("Invalid!\n");
            fflush(stdin);
            // If input was wrong we change day to 0 to invalidate checkDate function in the while loop.
            newDate.day = 0;
        }
        else
        {
            if (!checkDate(newDate) || isDateInFuture(newDate))
            {
                printf("Invalid or unreasonable date, try again.\n");
            }
        }

    } while (!checkDate(newDate) || isDateInFuture(newDate));

    return newDate;
}

bool validStartcode(int code)
{
    DEBUG("Checking startcode");
    return (code >= 100000 && code <= 999999);
}

bool validIdcode(int code)
{
    return (code >= 1000000 && code <= 9999999);
}