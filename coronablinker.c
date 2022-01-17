#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void handleChoice(void)
{
    int choice = 0;

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
            // call startcode function
            break;
        case 2:
            // call another input func
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
    printf("testtest\n")
    return 0;
}