#include "watched.h"
#include "movie.h"

void writeNewWatched(Watched watched) {
    FILE * watches;

    watches = fopen("./data/watched.csv","a+");

    fprintf(watches, "%d,%d,%.2f,%d/%d/%d\n", watched.user_id, watched.movie_id, watched.user_avaliation, watched.day, watched.month, watched.year);

    fclose(watches);
}

void showHistory(int user_id){
    Watched *history;
    int i, isValidOption, manyWatched;
    char temp,firstEntry;

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
            i = 0;
            while((temp = getchar()) != '\n')
            {
                if(i == 0 && temp != 'D' && temp != 'N') isValidOption = 0;
                if(i == 1) isValidOption = 0;
                if(i == 0) firstEntry = temp;
                i++;
            }
            if(i == 0) isValidOption = 0;

        }while(!isValidOption);

        if(firstEntry == 'D'){
            sortWatchedByDate(history, manyWatched);
        }else if(firstEntry == 'N'){
            sortWatchedByAvaliation(history, manyWatched);
        }
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
        
        watched.user_id = atoi(row[0]);
        watched.movie_id = atoi(row[1]);
        watched.user_avaliation = atof(row[2]);
        watched.day = atoi(row[3]);
        watched.month = atoi(row[4]);
        watched.year = atoi(row[5]);

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
    int i, j;
    Watched aux;
    Watched *temp;
    Movie movie;

    //temp = (Watched*) calloc(manyWatched,sizeof(Watched));

    temp = watched;

    //sort by year
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].year < temp[j + 1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    //sort by month
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].month < temp[j + 1].month && temp[j].year == temp[j+1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    //sort by day
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].day < temp[j + 1].day && temp[j].month == temp[j + 1].month && temp[j].year == temp[j + 1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    i=0;
    printf("Meu historico:\n");
    for(i = 0; i < manyWatched; i++){
        movie = getMovieByID(temp[i].movie_id);
        printf("\t%d/%d/%d - %s: %.2f\n",temp[i].day,temp[i].month,temp[i].year,movie.title,temp[i].user_avaliation);
        free(movie.title);
        free(movie.description);
    }

    
}

void sortWatchedByAvaliation(Watched *watched, int manyWatched){
    int i, j;
    Watched aux;
    Watched *temp;
    Movie movie;

    //temp = (Watched*) calloc(manyWatched,sizeof(Watched));

    temp = watched;

    //sort by year
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].year < temp[j + 1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    //sort by month
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].month < temp[j + 1].month && temp[j].year == temp[j+1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    //sort by day
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].day < temp[j + 1].day && temp[j].month == temp[j + 1].month && temp[j].year == temp[j + 1].year){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    //sort by avaliation
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(temp[j].user_avaliation < temp[j + 1].user_avaliation){
                aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    i=0;
    printf("Meu historico:\n");
    for(i = 0; i < manyWatched; i++){
        movie = getMovieByID(temp[i].movie_id);
        printf("\t%d/%d/%d - %s: %.2f\n",temp[i].day,temp[i].month,temp[i].year,movie.title,temp[i].user_avaliation);
        free(movie.title);
        free(movie.description);
    }
}