#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "input.h"

// TODO change return type if necessary
int enterStartCode(void)
{
    int startCode;
    printf("Please enter your start code: ");
    scanf("%d", &startCode);
    printf("Start code accepted!\n");
    return startCode;
}

//  TODO change return type if necessary
int enterIdCode(void)
{
    int idCode;
    printf("Please enter your ID code: ");
    scanf("%d", &idCode);
    printf("ID code accepted! \n");
    return idCode;
}

bool isValidInput(int input)
{
    if (isdigit(input))
    {
        return true;
    }
    else
    {
        return false;
    }
}