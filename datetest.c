#include "date.h"
#include <stdio.h>

#define TEST_CASE(name) printf("\nRUNNING CASE: %s\n", name)
#define VERIFY(cond, msg)             \
    if (cond)                         \
        printf("SUCCESS: %s\n", msg); \
    else                              \
        printf("FAIL: %s\n", msg);

int main(void)
{
    date date1, date2;

    TEST_CASE("Testing setDate");
    setDate(&date1, 1, 2, 2021);
    printf("%d.%d.%d\n", date1.day, date1.month, date1.year);

    TEST_CASE("Testing checkDate");
    VERIFY(checkDate(date1), "Date is valid");
    setDate(&date1, 31, 2, 2021);
    VERIFY(!checkDate(date1), "Date is not valid");
    setDate(&date1, 29, 2, 2021);
    VERIFY(!checkDate(date1), "Date is not valid");
    setDate(&date1, 29, 2, 2020);
    VERIFY(checkDate(date1), "Date is valid");

    TEST_CASE("Testing isLeapYear");
    setDate(&date1, 29, 2, 2020);
    VERIFY(isLeapYear(date1), "Date is on a leap year");
    setDate(&date1, 29, 2, 2021);
    VERIFY(!isLeapYear(date1), "Date is not on a leap year");
    setDate(&date1, 1, 2, 2021);
    VERIFY(!isLeapYear(date1), "Date is not on a leap year");
    setDate(&date1, 1, 2, 1900);
    VERIFY(!isLeapYear(date1), "Date is not on a leap year");
    setDate(&date1, 29, 2, 2000);
    VERIFY(isLeapYear(date1), "Date is on a leap year");

    TEST_CASE("Testing printFiStd");
    printFiStd(date1);
    printf("\n");

    TEST_CASE("Testing getDaysPerMonth");
    printf("%d days in month %d year %d\n", getDaysPerMonth(date1), date1.month, date1.year);
    setDate(&date1, 29, 2, 2020);
    printf("%d days in month %d year %d\n", getDaysPerMonth(date1), date1.month, date1.year);
    setDate(&date1, 29, 2, 2021);
    printf("%d days in month %d year %d\n", getDaysPerMonth(date1), date1.month, date1.year);
    setDate(&date1, 29, 3, 2020);
    printf("%d days in month %d year %d\n", getDaysPerMonth(date1), date1.month, date1.year);
    setDate(&date1, 29, 8, 2020);
    printf("%d days in month %d year %d\n", getDaysPerMonth(date1), date1.month, date1.year);

    TEST_CASE("Testing isBefore");
    setDate(&date2, 29, 3, 2020);
    VERIFY(isBefore(date2, date1), "Date2 is before Date1");
    VERIFY(!isBefore(date1, date2), "Date1 is not before Date2");
    setDate(&date1, 29, 3, 2021);
    VERIFY(isBefore(date2, date1), "Date2 is before Date1");
    VERIFY(!isBefore(date1, date2), "Date1 is not before Date2");
    setDate(&date1, 31, 3, 2020);
    VERIFY(isBefore(date2, date1), "Date2 is before Date1");
    VERIFY(!isBefore(date1, date2), "Date1 is not before Date2");

    TEST_CASE("Testing getPreviousDay");
    printf("Current date is ");
    printFiStd(date1);
    printf("   Yesterdays date was: ");
    printFiStd(getPreviousDay(date1));
    setDate(&date2, 1, 1, 2020);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   Yesterdays date was: ");
    printFiStd(getPreviousDay(date2));
    setDate(&date2, 1, 3, 2020);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   Yesterdays date was: ");
    printFiStd(getPreviousDay(date2));
    setDate(&date2, 1, 3, 2021);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   Yesterdays date was: ");
    printFiStd(getPreviousDay(date2));
    setDate(&date2, 1, 2, 2021);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   Yesterdays date was: ");
    printFiStd(getPreviousDay(date2));
    printf("\n");

    TEST_CASE("Testing getNDaysPrevious");
    setDate(&date2, 1, 2, 2021);
    printf("Current date is ");
    printFiStd(date2);
    printf("   %d days ago the date was: ", 21);
    printFiStd(getNDaysPrevious(date2, 21));
    setDate(&date2, 30, 1, 2021);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   %d days ago the date was: ", 10);
    printFiStd(getNDaysPrevious(date2, 10));
    setDate(&date2, 30, 1, 2021);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   %d days ago the date was: ", 35);
    printFiStd(getNDaysPrevious(date2, 35));
    setDate(&date2, 28, 2, 2021);
    printf("\nCurrent date is ");
    printFiStd(date2);
    printf("   %d days ago the date was: ", 75);
    printFiStd(getNDaysPrevious(date2, 75));

    return 0;
}