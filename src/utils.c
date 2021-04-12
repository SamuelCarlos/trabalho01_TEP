#include "../include/utils.h"

int verifyValidDate(int day, int month, int year) {
    if(year > 0){
        if(month >= 1 && month <= 12) {
            if(day >= 1 && day <= daysOnMonth(month, year)) {
                return 1;
            } 
            return 0;
        }
        return 0;
    }
    return 0;
}

int daysOnMonth(int month, int year)
{
    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12))
    {
        return 31;
    }
    else if (month == 2)
    {
        if (leapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
    else
    {
        return 30;
    }
}

int leapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isAlphanumeric(char c) {
    if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        return 1;
    } else {
        return 0;
    }
}

int isNumber(char c) {
    if (c >= '0' && c <= '9'){ 
        return 1; 
    } else {
        return 0;
    }
}

char *toUpperString(char *string) {
    int i;
    char * uppercased;

    uppercased = (char* ) calloc(strlen(string), sizeof(char));

    for(i = 0; i < strlen(string); i++) {
        if(!isupper(string[i])) 
        {
            uppercased[i] = toupper(string[i]);
        }
        else
        {
            uppercased[i] = string[i];
        }
    }


    return uppercased;
}

char inputVerificatorSingle (const int verbosity) {
    int isValidInformation = 1, i;
    char option, temp;

    do{
        if(!isValidInformation) if(verbosity) printf("\tPor favor digite uma entrada valida: ");
        isValidInformation = 1;
        i = 0;
        while((temp = getchar()) != '\n'){
            if(i == 0) {
                option = temp;
            };
            if(i > 0) isValidInformation = 0;
            i++;
        };
        if(i == 0) isValidInformation = 0;
    }while(!isValidInformation);

    return option;
}