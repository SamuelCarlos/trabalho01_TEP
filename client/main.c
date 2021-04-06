#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

/* 
Note that "menu.h" is the library who controlls 
once it don't use buffer to keep and pass data, 
we didn't need to pass several arguments to funtions. 
*/

/*
This is the beggining of the project,
we limited argv to only one option because
it's the only option used.
*/
int main(int argc, char* argv[]){
    int trash;

    // checks verbosity and defines its value as a const,
    // modifying it is not allowed
    if(!argv[1]) {
        printf("Por favor, defina a verbosidade.\n");
        return 0;
    }else{
        const int verbosity = atoi(argv[1]);
        if(verbosity != 0 && verbosity != 1) {
            printf("Verbosidade invalida, digite 1 ou 0.\n");
            return 0;
        }
        if(verbosity) trash = system("clear");
        startMenu(verbosity);
    }
    
    return 0;
}