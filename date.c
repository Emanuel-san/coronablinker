#include "date.h"
#include <time.h>
#include <stdio.h>

const int daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool isLeapYear(date date)
{
    // true if the year i divisible by 4 but not by both 4 and 100, except if its also divisible by 400.
    return date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0);
}

int getDaysPerMonth(date date)
{
    if (date.month == 2 && isLeapYear(date))
    {
        return 29;
    }
    else
    {
        return daysInMonth[date.month];
    }
}

bool checkDate(date date)
{
    // true if day, month and year is correct, else false
    return (date.month <= 12 && date.month > 0 && date.day > 0 && date.day <= getDaysPerMonth(date)) && (date.month > 0 && date.month <= 12) && date.year > 2019;
}

void setDate(date *date, int day, int month, int year)
{
    date->day = day;
    date->month = month;
    date->year = year;
}

void printFiStd(date date)
{
    printf("%d.%d.%d", date.day, date.month, date.year);
}

bool isBefore(date first, date second)
{
    if (first.year < second.year)
    {
        return true;
    }
    else if (first.year > second.year)
    {
        return false;
    }
    else if (first.month < second.month)
    { // first.year==second.year
        return true;
    }
    else if (first.month > second.month)
    {
        return false;
    }
    else if (first.day < second.day)
    { // first.year==second.year && first.month==second.month
        return true;
    }
    else
    { // first.day>second.day || dates equal
        return false;
    }
}

date getPreviousDay(date date)
{
    if (date.day == 1)
    {
        // Beginning of month, get previous month
        date.month = date.month - 1;
        if (date.month == 0)
        {
            // Beginning of year, skip to December previous year
            date.year -= 1;
            date.month = 12;
        }
        // Update the day to the last day of the previous month
        date.day = getDaysPerMonth(date);
    }
    else
    {
        // Not in beginning of month, just decrease day.
        date.day -= 1;
    }
    return date;
}

date getNDaysPrevious(date aDate, int days)
{
    date indexDate = aDate;
    while (days > 0)
    {
        indexDate = getPreviousDay(indexDate);
        days--;
    }
    return indexDate;
}

void setToToday(date *date)
{
    time_t todayInSeconds;
    struct tm *timeinfo;
    todayInSeconds = time(NULL);
    timeinfo = localtime(&todayInSeconds);

    date->day = timeinfo->tm_mday;
    date->month = timeinfo->tm_mon + 1;    // tm_mon is months since Januray e.g January=0
    date->year = timeinfo->tm_year + 1900; // tm_year is years since 1900
}

bool isDateInFuture(date aDate)
{
    date today;
    setToToday(&today);
    if (isBefore(today, aDate))
    {
        return true;
    }
    else
    {
        return false;
    }
}