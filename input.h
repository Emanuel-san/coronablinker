#ifndef INPUTH___
#define INPUTH___

#include "date.h"

/**
 * @brief Function for entering a startcode.
 *
 * @returns an accepted startcode.
 */
int enterStartCode(void);

/**
 * @brief Function to simulate input of a units identification code by manual input.
 *
 * @returns an accepted identification code.
 */
int enterIdCode(void);

/**
 * @brief Function for user input of date.
 *
 * @returns A date struct.
 */
date enterDate(void);

/**
 * @brief Function to validate that given startcode is a 6 digit number.
 *
 * @param code Startcode.
 * @returns True if code is correct, else false.
 */

bool validStartcode(int code);

/**
 * @brief Function to validate that given startcode is a 7 digit number.
 *
 * @param code Identification code.
 * @returns True if code is correct, else false.
 */
bool validIdcode(int code);

#endif