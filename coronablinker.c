#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct date
{
    int day;
    int month;
    int year;
};
int getCurrentDays(int currentMonth)
{
    int daysInEachMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int currentDays = daysInEachMonth[currentMonth - 1];

    return currentDays;
}

// Checks for leap year
bool isLeapYear(int currentYear)
{
    // true if the year i divisible by 4 but not by both 4 and 100, except if its also divisible by 400.
    return currentYear % 4 == 0 && (currentYear % 100 != 0 || currentYear % 400 == 0);
}

bool checkDate(struct date *checkDate)
{

    int daysInEachMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (checkDate->month == 2 && isLeapYear(checkDate->year))
    {
        daysInEachMonth[1] = 29;
    }

    if (checkDate->day < 1 || checkDate->day > daysInEachMonth[checkDate->month - 1])
    {
    }
    // bool leapYear = false;
    // printf("%d.%d.%d\n", checkDate->day, checkDate->month, checkDate->year);
    // leapYear = isLeapYear(checkDate->year);
    // int daysInMonth = getCurrentDays(checkDate->month);
}

struct date enterDate(void)
{
    struct date newDate;
    do
    {
        printf("Enter date (DD.MM.YYYY): ");
        scanf("%d.%d.%d", &newDate.day, &newDate.month, &newDate.year);
    } while (!checkDate(&newDate));

    return newDate;
}
// Enter start code
// TODO change return type if necessary
int enterStartCode(void)
{
    int startCode;
    printf("Please enter your start code: ");
    scanf("%d", &startCode);
    printf("Start code accepted!\n");
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
    struct date newDate;
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
            newDate = enterDate();
            // printf("%d.%d.%d\n", newDate.day, newDate.month, newDate.year);
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