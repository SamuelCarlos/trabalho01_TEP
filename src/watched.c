#include "watched.h"

void writeNewWatched(Watched watched) {
    FILE * watches;

    watches = fopen("./data/watched.csv","a+");

    fprintf(watches, "%d,%d,%.2f,%d/%d/%d\n", watched.user_id, watched.movie_id, watched.user_avaliation, watched.day, watched.month, watched.year);

    fclose(watches);
}

void showHistory(int user_id){
    Watched *history;
    int optionSize, i, isValidOption, manyWatched;
    char temp;
    char *option;

    history = getUserHistory(user_id, &manyWatched);

    if(history[0].id == -2){
        printf("Ainda nao existe nenhum registro de historico.\n");
    }else if(history[0].id == -1){
        printf("Ainda nao existe nenhum registro de historico para o usuario.\n");
    }else{

        printf("Digite D para ordenar por Data.\n");
        printf("ou digite N para ordenar por Nota.\n");

        do{
            printf("-> ");
            isValidOption = 1;
            optionSize = 10;
            option = (char* ) calloc(optionSize, sizeof(char));
            i = 0;
            while((temp = getchar()) != '\n')
            {
                if(i == 0 && temp != 'D' || temp != 'N') isValidOption = 0;
                if(i == 1) isValidOption = 0;

                if((i + 1) == optionSize) 
                {
                    optionSize *= 2;
                    option = (char* ) realloc(option, optionSize * sizeof(char));
                }

                option[i] = temp;
                option[i + 1] = '\0';
                i++;
            }
        }while(!isValidOption);

        if(option == "D"){
            sortWatchedByDate(history, manyWatched);
        }else if(option == "N"){
            sortWatchedByAvaliation(history, manyWatched);
        }

        free(option);
    }

    free(history);
}

Watched *getUserHistory(int user_id, int *manyWatched){
    FILE *user_watched; // movies
    Watched watched; // movie
    Watched *history; // matches
    int i, end = 0, count = 0, found = 0, array_parser = 0, len, length;
    long unsigned int size;
    char *pointer, *pointer2, *token;
    char **row;

    user_watched = fopen("./data/watched.csv","r");

    history = (Watched* ) calloc((count + 1) , sizeof(Watched));

    if (user_watched == NULL) {
        history[0].id = -2;
        return history;
    }

    watched.id = 1;

    do {
        size = 0;
        len = getline(&pointer, &size, user_watched);
        if(len == -1){ 
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;
        
        row = (char** ) calloc(6, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        for(i = 1; i < 3; i++) {
            if(token == NULL) break;

            token = strtok_r(NULL, ",", &pointer);
            row[array_parser] = token;
            array_parser++;
        }
        array_parser = 0;

        for(i = 3; i < 6; i++){
            if(token == NULL) break;

            token = strtok_r(NULL, "/", &pointer);  
            row[i] = token;
        }
        
        watched.user_id = atoi(row[1]);
        watched.movie_id = atoi(row[2]);
        watched.user_avaliation = atof(row[3]);
        watched.day = atoi(row[4]);
        watched.month = atoi(row[5]);
        watched.year = atoi(row[6]);

        free(row);
        free(pointer2);

        if(user_id == watched.user_id){
            found = 1;
            if(count > 0) history = (Watched *) realloc(history, (count + 1) * sizeof(Watched));
            history[count] = watched;
            count++;
        }

        watched.id++;
    }while(!end);

    if(!found) {
        history[0].id = -1;
    }

    fclose(user_watched);
    
    *manyWatched = count;

    return history;
}

void sortWatchedByDate(Watched *watched, int manyWatched){
    int i, j, k;
    Watched aux;
    Watched *temp;

    temp = (Watched*) calloc(manyWatched,sizeof(Watched));

    for(i = 0; i < manyWatched; i++){
        for(j = 0; j < manyWatched; j++){
            for(k = 0; k < manyWatched - 1; k++){

            }
        }
    }
}