#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "list.h"

#define DAYS_IN_RANGE 21

void handleChoice(void)
{
    int choice = 0;
    int idCode = 0, startCode = 0;
    date newDate;
    idList list = createList();
    do
    {
        printf("1. Enter Startcode\n");
        printf("2. Enter ID code and date\n");
        printf("3. Receive alarm\n");
        printf("0. Quit\n");

        printf("Menu choice: ");
        char term;
        if (scanf("%d%c", &choice, &term) != 2 || term != '\n')
        {
            printf("Invalid choice!\n");
            fflush(stdin);
        }
        else
        {
            switch (choice)
            {
            case 1:
                enterStartCode(&startCode);
                deleteOldIdCodes(&list, DAYS_IN_RANGE);
                printListAll(list);
                break;
            case 2:
                enterIdCode(&idCode);
                newDate = enterDate();
                createNewNode(&list, newDate, idCode);

                break;
            case 3:
                printf("You've been exposed to corona!\n");
                break;
            case 0:
                destroyList(&list);
                printf("Good bye! Dont get sick, stay home, clean your hands, stay safe!\n");
                exit(1);
            default:
                printf("Invalid choice!\n");
            }
        }
    } while (1);
}

int main(void)
{

    handleChoice();

    return 0;
}