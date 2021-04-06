#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

int main(int argc, char* argv[1]){
    int trash;

    const int verbosity = atoi(argv[1]);
    if(verbosity) trash = system("clear");

    startMenu(verbosity);
    
    return 0;
}