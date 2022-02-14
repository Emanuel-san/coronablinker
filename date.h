#ifndef DATEH___
#define DATEH___

#include <stdbool.h>

typedef struct date_struct
{
    int day;
    int month;
    int year;
} date;

/**
 * Function for checking if a date is on a leap year
 * @param date The date to check
 * @returns true if the date is on a leap year
 */
bool isLeapYear(date date);

/**
 * Function for checking if a date is valid.
 * @param date The date to be checked.
 * @returns true if date is valid, false otherwise.
 */
bool checkDate(date date);

/**
 * @brief Function to set a dates data with day, month and year.
 *
 * @param date Date data to be set.
 * @param day Day that wils be set.
 * @param month Month that wils be set.
 * @param year Year that wils be set.
 */
void setDate(date *date, int day, int month, int year);

/**
 * Function for printing a date in Finnish standard format.
 * @param date The date to print.
 */
void printFiStd(date date);

/**
 * @brief Function for comparing two dates to see if one is after the other.
 * @param first The date we want to check if it is after in time.
 * @param second The date we want to check if it is before the first in time.
 * @returns true if first is after second, false otherwise.
 */
bool isAfter(date first, date second);

/**
 * @brief Function for comparing two dates to see if one is before the other.
 * @param first The date we want to check if it is first in time.
 * @param second The date we want to check if it is after the first in time.
 * @returns true if first is before second, false otherwise.
 */
bool isBefore(date first, date second);

/**
 * Get the number of days for the month of the given date
 * @param date The date to check
 * @returns an integer representing the maximun number of days in the given month,
 *          0 if the month is invalid
 */
int getDaysPerMonth(date date);

/**
 * Function for retrieving the date before a given day.
 * @param date The starting date.
 * @returns The day before the given date.
 */
date getPreviousDay(date date);

/**
 * Function for retreving the date for a given number of days before the given date.
 * @param date The starting date.
 * @param days The number of days to go back
 * @returns The date that is a given number of days before the given date
 */
date getNDaysPrevious(date date, int days);

/**
 * Function for setting a date to todays date.
 * @param date Pointer to the date to set to todays date.
 */
void setToToday(date *date);

/**
 * @brief Checks if a given date is before today.
 * @param aDate Date to be checked.
 * @returns true if the date given is before todays date, else false;
 */
bool isDateInFuture(date aDate);

/**
 * @brief Function to check if two dates are equal
 *
 * @param first The first date to check
 * @param second The second date to check
 * @return true if the dates are equal, false otherwise
 */
bool isEqual(date first, date second);

#endif