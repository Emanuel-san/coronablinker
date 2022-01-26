#ifndef INPUTH___
#define INPUTH___

#include "date.h"

// TODO dox
int enterStartCode(void);

// TODO dox
int enterIdCode(void);

/**
 * @brief Function to validate that given startcode is a 6 digit number.
 *
 * @param code digit code.
 * @returns True if correct, else false.
 */
bool validStartcode(int code);

#endif