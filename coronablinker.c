/* ToDo:
- Kolla att man inte matar in bokstäver istället för siffror (ctype.h)
- Hitta på bra begränsningar till startkod och IDkod
*/

#include <stdio.h>
#include <stdlib.h>
#include "date.h"
#include "input.h"

void handleChoice(void)
{
    int choice = 0;
    int startCode, idCode;
    struct date newDate;
    {
        printf("1. Enter Startcode\n");
        printf("2. Enter ID code and date\n");
        printf("3. Receive alarm\n");
        printf("0. Quit\n");

        printf("Menu choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid choice!\n");
            fflush(stdin);
        }
        else
        {
            switch (choice)
            {
            case 1:
                startCode = enterStartCode();
                printf("%d\n", startCode);
                break;
            case 2:
                idCode = enterIdCode();
                printf("%d\n", idCode);
                newDate = enterDate();
                printf("%d.%d.%d\n", newDate.day, newDate.month, newDate.year);
                break;
            case 3:
                // TODO make function later if needed
                printf("You've been exposed to corona!\n");
                break;
            case 0:
                printf("Good bye! Dont get sick, stay home, clean your hands, stay safe!\n");
                exit(1);
            default:
                printf("Invalid choice!\n");
            }
        }
    }
}

int main(void)
{
    while (1)
    {
        handleChoice();
    }
    return 0;
}