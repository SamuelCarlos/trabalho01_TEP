#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *toUpperString(char *string);

int daysOnMonth(int month, int year);

int leapYear(int year);

int isNumber(char c);

int verifyValidDate(int day, int month, int year);

/*
@brief verifies if an given char is alphanumeric
@return 1: alphanumeric
        0: not alphanumeric
*/
int isAlphanumeric(char c);

#endif //utils_h