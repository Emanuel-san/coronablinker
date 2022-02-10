#include "date.h"
#include <stdio.h>
#include "unittest.h"

bool isEqual(date first, date second)
{
    return (first.year == second.year && first.month == second.month && first.day == second.day);
}

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
    setDate(&date1, 1, 1, 2020);
    VERIFY(getDaysPerMonth(date1), "Month 1 is a valid month");
    setDate(&date1, 1, 6, 2020);
    VERIFY(getDaysPerMonth(date1), "Month 6 is a valid month");
    setDate(&date1, 1, 12, 2020);
    VERIFY(getDaysPerMonth(date1), "Month 12 is a valid month");
    setDate(&date1, 1, 13, 2020);
    VERIFY(!getDaysPerMonth(date1), "Month 13 is not a valid month");
    setDate(&date1, 1, 0, 2020);
    VERIFY(!getDaysPerMonth(date1), "Month 0 is not a valid month");
    setDate(&date1, 1, 29999, 2020);
    VERIFY(!getDaysPerMonth(date1), "Month 29999 is not a valid month");
    printf("\n");

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

    TEST_CASE("Testing isBefore");
    setDate(&date2, 29, 3, 2020);
    VERIFY(!isAfter(date2, date1), "Date2 is not after Date1");
    VERIFY(isAfter(date1, date2), "Date1 is after Date2");
    setDate(&date1, 29, 3, 2021);
    VERIFY(!isAfter(date2, date1), "Date2 is not after Date1");
    VERIFY(isAfter(date1, date2), "Date1 is after Date2");
    setDate(&date1, 31, 3, 2020);
    VERIFY(!isAfter(date2, date1), "Date2 is not after Date1");
    VERIFY(isAfter(date1, date2), "Date1 is after Date2");

    TEST_CASE("Testing getPreviousDay");
    setDate(&date1, 29, 2, 2020);
    setDate(&date2, 1, 3, 2020);
    date2 = getPreviousDay(date2);
    VERIFY(isEqual(date1, date2), "stepping back 1.3.2020 one day");
    setDate(&date1, 31, 12, 2020);
    setDate(&date2, 1, 1, 2021);
    date2 = getPreviousDay(date2);
    VERIFY(isEqual(date1, date2), "stepping back 1.1.2021 one day");
    setDate(&date1, 5, 6, 2022);
    setDate(&date2, 6, 6, 2022);
    date2 = getPreviousDay(date2);
    VERIFY(isEqual(date1, date2), "stepping back 6.6.2022 one day");
    printf("\n");

    TEST_CASE("testing getNDaysPrevious.");
    setDate(&date1, 31, 1, 2020);
    setDate(&date2, 11, 1, 2020);
    date1 = getNDaysPrevious(date1, 20);
    VERIFY(isEqual(date1, date2), "Stepping back 31.1.2020 20 days");
    setDate(&date1, 10, 3, 2020);
    setDate(&date2, 20, 12, 2019);
    date1 = getNDaysPrevious(date1, 81);
    VERIFY(isEqual(date1, date2), "Stepping back 10.3.2020 81 days");
    printf("\n");

    TEST_CASE("Testing setToToday");
    setToToday(&date1);
    printf("Today is: ");
    printFiStd(date1);
    printf("\n");

    TEST_CASE("Testing isDateInFuture");
    VERIFY(!isDateInFuture(date1), "Date is not in future");
    setDate(&date1, 28, 2, 2021);
    VERIFY(!isDateInFuture(date1), "Date is not in future");
    setDate(&date1, 28, 2, 2023);
    VERIFY(isDateInFuture(date1), "Date is in future");
    setDate(&date1, 28, 1, 2023);
    VERIFY(isDateInFuture(date1), "Date is in future");
    setDate(&date1, 26, 1, 2022);
    VERIFY(!isDateInFuture(date1), "Date is not in future");
    printf("\n");

    TEST_CASE("Testing isAfter");
    setDate(&date2, 10, 2, 2020);
    setDate(&date1, 20, 2, 2020);
    VERIFY(isAfter(date1, date2), "Different days, are after");
    setDate(&date1, 5, 2, 2020);
    VERIFY(!isAfter(date1, date2), "Different days, are not after");

    setDate(&date1, 10, 3, 2020);
    VERIFY(isAfter(date1, date2), "Different months, are after");
    setDate(&date1, 10, 1, 2020);
    VERIFY(!isAfter(date1, date2), "Different months, are not after");

    setDate(&date1, 10, 2, 2021);
    VERIFY(isAfter(date1, date2), "Different years, are after");
    setDate(&date1, 10, 1, 2019);
    VERIFY(!isAfter(date1, date2), "Different years, are not after");

    setDate(&date1, 10, 2, 2020);
    VERIFY(!isAfter(date1, date2), "Date is not after itself (equal)");
    return 0;
}