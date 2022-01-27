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
    date date1;

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

    return 0;
}