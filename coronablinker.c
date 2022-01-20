/* ToDo:
- Dela upp i olika filer, typ datum i en
- Kolla att datum inte är i framtiden
- Kolla att man inte matar in bokstäver istället för siffror (ctype.h)
- Hitta på bra begränsningar till startkod och IDkod
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
struct date
{
    int day;
    int month;
    int year;
};

// Checks for leap year
bool isLeapYear(int currentYear)
{
    // true if the year i divisible by 4 but not by both 4 and 100, except if its also divisible by 400.
    return currentYear % 4 == 0 && (currentYear % 100 != 0 || currentYear % 400 == 0);
}

// checks id date is valid
bool checkDate(struct date *date)
{

    int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date->month == 2 && isLeapYear(date->year))
    {
        daysInMonth[2] += 1;
    }
    // true if day, month and year is correct, else false
    return (date->day > 0 && date->day <= daysInMonth[date->month]) && (date->month > 0 && date->month <= 12) && date->year >= 2019;
}

// Enter date
struct date enterDate(void)
{
    struct date newDate;
    do
    {
        printf("Enter date (DD.MM.YYYY): ");
        scanf("%d.%d.%d", &newDate.day, &newDate.month, &newDate.year);
        if (!checkDate(&newDate))
        {
            printf("Invalid date, try again!\n");
        }
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

int main(void)
{
    while (1)
    {
        handleChoice();
    }
    return 0;
}