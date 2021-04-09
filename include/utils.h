#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
@brief transform an string to uppercase;
@param char *string: string to be uppercased;
@return uppercased string;
*/
char *toUpperString(char *string);

/*
@brief calculates how many days a specific month have;
@param int month: month's specific integer (1 from 12);
@param int year: year's number;
@return >0: how many days a month have;
        -1: given month or year are not accepted;
*/
int daysOnMonth(int month, int year);


/*
@brief calculates if a given year is leap or not;
@param int year: year's number;
@return 1: leap year;
        0: not leap year;
*/
int leapYear(int year);

/*
@brief calculates if a given char is a number;
@param char c: character;
@return 1: is a number;
        0: NAN;
*/
int isNumber(char c);

/*
@brief calculates if a given date is valid;
@param int day: day's number;
@param int month: month's number;
@param int year: year's number;
@return 1: valid date;
        0: not valid date;
*/
int verifyValidDate(int day, int month, int year);

/*
@brief verifies if an given char is alphanumeric;
@param char c: character;
@return 1: alphanumeric;
        0: not alphanumeric;
*/
int isAlphanumeric(char c);


/*
@brief catch up user input while its a valid single char input;
@param const int verbosity: defines if menus are about to be printed;
@return char: valid input;
*/
char inputVerificatorSingle(const int verbosity);

#endif //utils_h