#include "../include/watched.h"
#include "../include/movie.h"
#include "../include/user.h"
#include "../include/utils.h"

void writeNewWatched(Watched watched) {
    FILE * watches;

    watches = fopen("./data/watched.csv","a+");

    fprintf(watches, "%d,%d,%.2f,%d/%d/%d\n", watched.user_id, watched.movie_id, watched.user_avaliation, watched.day, watched.month, watched.year);

    fclose(watches);
}

void showHistory(const int verbosity, const int user_id){
    User user;
    Watched *history;
    int i, isValidOption, manyWatched;
    char temp,firstEntry;

    history = getUserHistory(user_id, &manyWatched);

    if(history[0].id == -2){
        if(verbosity) printf("\tAinda nao existe nenhum registro de historico.\n");
    }else if(history[0].id == -1){
        if(verbosity) printf("\tAinda nao existe nenhum registro de historico para o usuario.\n");
    }else{

        if(verbosity) printf("\tDigite D para ordenar por Data.\n");
        if(verbosity) printf("\tou digite N para ordenar por Nota.\n");
        /**
         * Loop to verify if user's input is a valid entry;
        */
        do{
            if(verbosity) printf("\t-> ");
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

        printf("Nome: %s\n", user.login);
        printf("Meu historico:\n");

        free(user.login);
        free(user.password);
        /**
         * ordering and printing the history;
        */
        if(firstEntry == 'D'){
            sortWatchedByDate(history, manyWatched);
        }else if(firstEntry == 'N'){
            sortWatchedByAvaliation(history, manyWatched);
        }
    }
    free(history);
}

Watched *getUserHistory(const int user_id, int *manyWatched){
    FILE *user_watched;
    Watched watched;
    Watched *history;
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
    /**
     * Loop to get all lines from the "watched.csv" file 
     * and save the history to the pointer 
     * if the line contains the user's id passed by user;
    */
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
    /**
     * counts how many movies the user watched;
    */ 
    *manyWatched = count;

    return history;
}

void sortWatchedByDate(Watched *watched, int manyWatched){
    int i, j;
    Watched aux;
    Movie movie;

    /**
     * sort by year
    */
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].year < watched[j + 1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    /**
     * sort by month if the years are same;
    */
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].month < watched[j + 1].month && watched[j].year == watched[j+1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }

    /**
     * sort by day if the years and the months are same;
    */
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].day < watched[j + 1].day && watched[j].month == watched[j + 1].month && watched[j].year == watched[j + 1].year){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }
    /**
     * prints the ordered history;
    */ 
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
    /**
     * sort by avaliation;
    */
    for(i = 1; i < manyWatched; i++){
        for(j = 0; j < manyWatched - i; j++){
            if(watched[j].user_avaliation < watched[j + 1].user_avaliation){
                aux = watched[j];
                watched[j] = watched[j + 1];
                watched[j + 1] = aux;
            }
        }
    }
    /**
     * prints the ordered history;
    */ 
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

void watchMovie(const int verbosity, const int user_id, const int movie_id) {
    int isValidOption = 1, i = 0;
    int optionSize;
    char temp;
    char *option;
    Watched watched;

    watched.user_id = user_id;
    watched.movie_id = movie_id;

    if(verbosity) printf("Digite sua nota para o filme: ");
    /**
     * Loop to verify if user's input is a valid entry;
    */
    do {
        if(!isValidOption)
        {
            free(option);
            if(verbosity) printf("Digite uma opcao valida: ");
            isValidOption = 1;  
        }

        optionSize = 10;
        option = (char* ) calloc(optionSize, sizeof(char));
        i = 0;
        while((temp = getchar()) != '\n')
        {
            if(i <= 4) {
                if(!isNumber(temp)) 
                {
                    if (temp != '.') isValidOption = 0;

                    if (i > 2) isValidOption = 0;
                }

                if((i + 1) == optionSize) 
                {
                    optionSize *= 2;
                    option = (char* ) realloc(option, optionSize * sizeof(char));
                }

                option[i] = temp;
                option[i + 1] = '\0';
                i++;

                if(isValidOption && atof(option) > 10) isValidOption = 0;
            }
        }
    } while(!isValidOption);

    if(i == 0) {
        watched.user_avaliation = -1;
    }else{
        watched.user_avaliation = atof(option);
    }

    free(option);

    if(verbosity) printf("Data de quando assistiu.\n");
    /**
     * loop to get the date that the user watched the movie
     * verify if is a valid date;
    */
    do{
        if(verbosity) printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        while(scanf("%d/%d/%d", &watched.day, &watched.month, &watched.year) != 3){
            while(temp = getchar() != '\n'){};
            if(verbosity) printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        } 
        getchar();
    }while(!verifyValidDate(watched.day, watched.month, watched.year));

    writeNewWatched(watched);
}
