#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Enter start code
// TODO change return type if necessary
int enterStartCode(void)
{
    int startCode;
    printf("Please enter your start code: ");
    scanf("%d", &startCode);
    printf("Start code accepted! \n");
    return startCode;
}

// Enter ID code
//  TODO change return type if necessary
int enterIdCode(void)
{
    int idCode;
    printf("Please enter your ID code: ");
    scanf("%d", &idCode);
    printf("ID code accepted! \n");
    return idCode;
}

void handleChoice(void)
{
    int choice = 0;
    int startCode, idCode;
    {
        printf("1. Enter Startcode\n");
        printf("2. Enter ID code and date\n");
        printf("3. Receive alarm\n");
        printf("0. Quit\n");

        printf("Menu choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            startCode = enterStartCode();
            printf("%d\n", startCode);
            break;
        case 2:
            idCode = enterIdCode();
            printf("%d\n", idCode);
            // call date func
            break;
        case 3:
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

int main(void)
{
    while (1)
    {
        handleChoice();
    }
    return 0;
}