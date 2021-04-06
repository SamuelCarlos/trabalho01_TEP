#include "watched.h"
#include "movie.h"
#include "user.h"

void writeNewWatched(Watched watched) {
    FILE * watches;

    watches = fopen("./data/watched.csv","a+");

    fprintf(watches, "%d,%d,%.2f,%d/%d/%d\n", watched.user_id, watched.movie_id, watched.user_avaliation, watched.day, watched.month, watched.year);

    fclose(watches);
}

void showHistory(int user_id){
    User user;
    Watched *history;
    int i, isValidOption, manyWatched;
    char temp,firstEntry;

    history = getUserHistory(user_id, &manyWatched);

    if(history[0].id == -2){
        printf("\tAinda nao existe nenhum registro de historico.\n");
    }else if(history[0].id == -1){
        printf("\tAinda nao existe nenhum registro de historico para o usuario.\n");
    }else{

        printf("\tDigite D para ordenar por Data.\n");
        printf("\tou digite N para ordenar por Nota.\n");

        do{
            printf("\t-> ");
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

        user = getUserById(user_id);

        printf("\tNome: %s\n", user.login);
        printf("\tMeu historico:\n");

        free(user.login);
        free(user.password);

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
    Movie movie;

    //sort by year
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].year < watched[j + 1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    //sort by month
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].month < watched[j + 1].month && watched[j].year == watched[j+1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    //sort by day
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].day < watched[j + 1].day && watched[j].month == watched[j + 1].month && watched[j].year == watched[j + 1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    for(i = 0; i < manyWatched; i++){
        movie = getMovieByID(watched[i].movie_id);
        if(watched[i].user_avaliation < 0){
        printf("\t%.2d/%.2d/%.4d - %s: Sem avaliacao\n",watched[i].day,watched[i].month,watched[i].year,movie.title);
        }else{
        printf("\t%.2d/%.2d/%.4d - %s: %.2f\n",watched[i].day,watched[i].month,watched[i].year,movie.title,watched[i].user_avaliation);
        }
        free(movie.title);
        free(movie.description);
    }

    
}

void sortWatchedByAvaliation(Watched *watched, int manyWatched){
    int i, j;
    Watched aux;
    Movie movie;

    //sort by avaliation
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].user_avaliation < watched[j + 1].user_avaliation){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    for(i = 0; i < manyWatched; i++){
        movie = getMovieByID(watched[i].movie_id);
        if(watched[i].user_avaliation < 0){
            printf("\tSem avaliacao - %s: %.2d/%.2d/%.4d\n", movie.title,watched[i].day,watched[i].month,watched[i].year);
        }else{
            printf("\t%.2f - %s: %.2d/%.2d/%.4d\n",watched[i].user_avaliation, movie.title,watched[i].day,watched[i].month,watched[i].year);
        }
        free(movie.title);
        free(movie.description);
    }
}