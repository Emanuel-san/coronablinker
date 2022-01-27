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
int enterStartCode(void)
{

    int startCode;
    do
    {
        printf("Please enter your start code: ");
        char term;
        if (scanf("%d%c", &startCode, &term) != 2 || term != '\n')
        {
            printf("Invalid input.\n");
            fflush(stdin);
            startCode = 0;
        }

        else if (!validStartcode(startCode))
        {
            printf("Invalid startcode.\n");
        }

    } while (!validStartcode(startCode));

    printf("**********************\nStart code accepted! Compressing data and sending to server.\n");
    return startCode;
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
            {

                printf("Invalid input.\n");
                fflush(stdin);
                idCode = 0;
            }
        }
        else if (!validIdcode(idCode))
        {
            printf("Invalid idcode.\n");
        }
    } while (!validIdcode(idCode));
    printf("ID code accepted!\n");
    return idCode;
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