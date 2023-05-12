/**
 * @file errors.h
 * @author Daniels Fišers
 * @brief This file contains error definitions that are used across the program
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef ERRORS
#define ERRORS

typedef enum
{
    NO_ERROR =          0,
    OUT_OF_RANGE =      2,
    DOESNT_EXIST =      3,
    DISABLED =          4,
    TRIES_EXCEEDED =    5,
    MISC_ERROR =        6
} Errors;

#endif // ERRORS
