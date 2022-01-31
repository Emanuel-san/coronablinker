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
        printf("Please enter your start code: ");
        char term;
        if (scanf("%d%c", startcode, &term) != 2 || term != '\n')
        {
            printf("Invalid input.\n");
            fflush(stdin);
            *startcode = 0;
        }

        else if (!validStartcode(*startcode))
        {
            printf("Invalid startcode.\n");
        }

    } while (!validStartcode(*startcode));

    printf("**********************\nStart code accepted! Compressing data and sending to server.\n");
}

//  TODO change return type if necessary
int enterIdCode(void)
{
    int idCode;
    char term;
    do
    {
        printf("Please enter your ID code: ");

        if (scanf("%d%c", &idCode, &term) != 2 || term != '\n')
        {
            printf("Invalid input.\n");
            fflush(stdin);
            idCode = 0;
        }
        else if (!validIdcode(idCode))
        {
            printf("Invalid idcode.\n");
        }
    } while (!validIdcode(idCode));
    printf("ID code accepted!\n");
    return idCode;
}

date enterDate(void)
{
    date newDate;
    int day, month, year;
    do
    {
        printf("Enter date (DD.MM.YYYY): ");
        char term;
        if (scanf("%d.%d.%d%c", &day, &month, &year, &term) != 4 || term != '\n')
        {
            printf("Invalid!\n");
            fflush(stdin);
            // If input was wrong we change day to 0 to invalidate checkDate function in the while loop.
            newDate.day = 0;
        }
        else
        {
            setDate(&newDate, day, month, year);

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