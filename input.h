#ifndef INPUTH___
#define INPUTH___

#include "date.h"

/**
 * @brief Function for entering a startcode.
 * @param startCode A pointer to the start code we want to change
 *
 */
void enterStartCode(int *startCode);

/**
 * @brief Function to simulate input of a units identification code by manual input.
 * @param idCode A pointer to the ID code we want to change
 *
 */
void enterIdCode(int *idCode);

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
 * @returns true if code is correct, else false.
 */

bool validStartcode(int code);

/**
 * @brief Function to validate that given startcode is a 7 digit number.
 *
 * @param code Identification code.
 * @returns true if code is correct, else false.
 */
bool validIdcode(int code);

#endif