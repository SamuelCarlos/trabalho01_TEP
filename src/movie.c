#include "../include/movie.h"
#include "../include/watched.h"
#include "../include/utils.h"


void listTenMovies(const int verbosity, const int user_id)
{
    int end = 0, i, j = 0;
    int error = 0;
    int trash;
    int movieQnt;
    int inputSize;
    int actualPage = 0;
    int verificator = 1;
    int optionNumber;
    int isValidOption = 1;
    char temp;
    char *option;
    Movie movie;
    Movie *movies;
    Watched watched;


    do {
        /**
         * Loop to get ten movies using the function getMovieByID and prints on the screen;
        */
        do {
            movies = (Movie* ) calloc(10, sizeof(Movie));
            j = 0;
            movieQnt = 0;

            /**
             * Loop to get the movies data;
            */
            for (i = (actualPage * 10 + 1); i < (actualPage + 1) * 10; i++) 
            {   
                movies[j] = getMovieByID(i);


                if(movies[j].id == -2) {
                    if(verbosity) printf("Erro ao ler arquivo.\n");
                    error = 1;
                    break;
                }
                if(movies[j].id == -1){
                    end = 1;
                    break;
                }

                movieQnt++;
                j++;
            }
            if(error) 
            { 
                free(movies);
                break;
            }

            if(movieQnt < 9) movies = (Movie* ) realloc(movies, movieQnt * sizeof(Movie));
            
            if(verbosity) printf("_____________________________________________________\n");
            if(verbosity) printf("|  ID |   Titulo                                    |\n"); 
            if(verbosity) printf("|-----|---------------------------------------------|\n");

            /**
             * Loop to print the movies data;
            */
            for (i = 0; i < movieQnt; i++){
                printf("%d- %s\n", movies[i].id, movies[i].title);
            }

            if(verbosity) printf("______|______________________________________________\n");

            if((actualPage > 0) && !end) {
                if(verbosity) printf("| < A |           voltar ao menu: 0           | M > |\n");
            }else if ((actualPage == 0) && !end){
                if(verbosity) printf("|                 voltar ao menu: 0           | M > |\n");
            }else if((actualPage > 0) && end) {
                if(verbosity) printf("| < A |           voltar ao menu: 0                 |\n");
            }else if((actualPage == 0) && end) {
                if(verbosity) printf("|                 voltar ao menu: 0                 |\n");
            }
            if(verbosity) printf("-----------------------------------------------------\n");
            
            if(verbosity) printf("Escolha seu filme ou navegue pelas paginas: ");
            /**
             * loop to verify if user's input is a valid entry;
            */
            do {
                if(!isValidOption){
                    if(verbosity) printf("Digite uma opcao valida: ");
                    free(option);
                    isValidOption = 1; 
                }
                inputSize = 10;
                option = (char* ) calloc(inputSize, sizeof(char));
                i = 0;
                while((temp = getchar()) != '\n'){
                    if(!isNumber(temp) && i > 0) isValidOption = 0;

                    if((i + 1) == inputSize) 
                    {
                        inputSize *= 2;
                        option = (char* ) realloc(option, inputSize * sizeof(char));
                    }
                    option[i] = temp;
                    option[i + 1] = '\0';
                    i++;
                }
            } while(!isValidOption);
             
            if(strcmp(option, "A") == 0 && actualPage > 0) {
                if(end) end = 0;
                actualPage--;
            }else if(strcmp(option, "M") == 0 && !end){
                actualPage++;
            }else if(strcmp(option, "M") == 0 && end){
                printf("Fim de filmes disponiveis\n");
                /**
                 *  Dont let page keep rolling if there's no movies left to show 
                 */
                if(movieQnt > 0){
                    actualPage++;
                }
            }else if(strcmp(option, "0") == 0){
                end = 1;
                verificator = 0;
            }else if(strlen(option) >= 1 && isNumber(option[0])){
                optionNumber = atoi(option);
                if ((optionNumber >= (actualPage * 10 + 1)) && (optionNumber < (actualPage + 1) * 10)) {
                    verificator = 0;

                    if(verbosity) trash = system("clear");
                    end = showMovie(verbosity, movies[(optionNumber % 10) - 1], user_id);
                }
            }

            for(i = 0; i < movieQnt; i++){
                free(movies[i].title);
                free(movies[i].description);
            }

            free(movies);
            free(option);

            if(verbosity) trash = system("clear");
        }while (verificator);

        verificator = 1;

        if(error) break;

    } while (!end);
}

Movie getMovieByID(const int id)
{
    FILE *movies;
    Movie movie;
    int i, found = 0, array_parser = 0, len, length;
    long unsigned int size;
    char *pointer, *pointer2, *token;
    char **row;

    movies = fopen("./data/filmes-grande.csv","r");
    if (movies == NULL) {
        movie.id = -2;
        return movie;
    }

    movie.id = 1;
    /**
     * Loop to found a movie by your ID;
    */
    do {
        size = 0;
        len = getline(&pointer, &size, movies);
        if(len == -1){
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;

        /**
         * If the movie ID is different, the function continues until it finds the right id;
         * When the ID is equal, the function reads the line and saves the movie data;
        */  
        if(movie.id == id) {

            row = (char** ) calloc(5, sizeof(char*));

            token = strtok_r(pointer, ",", &pointer);
            row[array_parser] = token;
            array_parser++;

            for(i = 1; i < 4; i++) {
                if(token == NULL) break;
                token = strtok_r(NULL, ",", &pointer);
                row[array_parser] = token;
                array_parser++;
            }
            array_parser = 0;

            token = strtok_r(pointer, "\"", &pointer);
            if(!token) token = strtok_r(NULL, "\"", &pointer);  
            row[4] = token;

            length = strlen(row[0]) + 1;
            movie.title = (char* ) calloc(length, sizeof(char));
            movie.title = strdup(row[0]);

            movie.year = atoi(row[1]);
            movie.duration = atoi(row[2]);
            movie.avaliation = atof(row[3]);

            length = strlen(row[4]) + 1;
            movie.description = (char* ) calloc(length, sizeof(char));
            movie.description = strdup(row[4]);

            /**
             * If the movie is found the loop ends;
            */
            found = 1;
            free(row);
        }
     
        free(pointer2);
        if(found) break;

        movie.id++;
    } while(!found);
 
    if(!found) {
        movie.id = -1;
    }
    fclose(movies);
    return movie;
}

Movie *getMovieMatches(char *string, int *movieCount) {
    FILE *movies;
    Movie movie;
    Movie *matches;
    int i, end = 0, count = 0, found = 0, array_parser = 0, len, length;
    long unsigned int size;
    char *pointer, *pointer2, *token, *uppercasedString, *uppercasedString2;
    char **row;

    movies = fopen("./data/filmes-grande.csv","r");

    matches = (Movie* ) calloc((count + 1) , sizeof(Movie));

    if (movies == NULL) {
        matches[0].id = -2;
        return matches;
    }

    movie.id = 1;

    /**
     * Loop to get all lines from the movie file
     * and compare the movie titles with the string passed by the user
     * if the string is a substring of the movie title save the movie in a pointer;
    */
    do {
        size = 0;
        len = getline(&pointer, &size, movies);
        if(len == -1){ 
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;
        
        row = (char** ) calloc(5, sizeof(char*));
        
        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        for(i = 1; i < 4; i++) {
            if(token == NULL) break;
            
            token = strtok_r(NULL, ",", &pointer);
            row[array_parser] = token;
            array_parser++;
        }
        array_parser = 0;

        token = strtok_r(pointer, "\"", &pointer);
        if(!token) token = strtok_r(NULL, "\"", &pointer);  
        row[4] = token;

        length = strlen(row[0]) + 1;
        movie.title = (char* ) calloc(length, sizeof(char));
        movie.title = strdup(row[0]);

        movie.year = atoi(row[1]);
        movie.duration = atoi(row[2]);
        movie.avaliation = atof(row[3]);

        length = strlen(row[4]) + 1;
        movie.description = (char* ) calloc(length, sizeof(char));
        movie.description = strdup(row[4]);
    
        free(row);
        free(pointer2);
        /**
         * Converts all letters in the string and each title to uppercase to compare;
        */
        uppercasedString = toUpperString(movie.title);
        uppercasedString2 = toUpperString(string);

        if(strstr(uppercasedString, uppercasedString2) != NULL) {
            found = 1;
            if(count > 0) matches = (Movie* ) realloc(matches, (count + 1) * sizeof(Movie));
            matches[count] = movie;
            count++;
        }else{
            free(movie.title);
            free(movie.description);
        }

        free(uppercasedString);
        free(uppercasedString2);

        movie.id++;
    }while(!end);

    if(!found) {
        matches[0].id = -1;
    }

    /**
     * Count how many movies matches with the given string;
    */
    *movieCount = count;

    fclose(movies);
    return matches;
}

int showMovie(const int verbosity, Movie movie, const int user_id) {
    int i = 0, trash, end = 0;
    int isValidOption = 1;
    char temp;
    char option;
  
    printMovieMetadata(movie);
    if(verbosity) printf("\t               O que deseja fazer?\n\n\t               1: Assistir\n\t               2: Voltar\n\t            -> ");
    /**
     * Loop to verify if user's input is a valid entry;
    */
    do {
        if(!isValidOption)
        {   
            if(verbosity) printf("Digite uma opcao valida: ");
            isValidOption = 1;  
        }
        i = 0;
        while((temp = getchar()) != '\n')
        {
            if(!isNumber(temp)) isValidOption = 0;
            if(i == 0) option = temp;
            i++;
        }
        if(i == 0) isValidOption = 0;
        if(i > 1) isValidOption = 0;
        if(option != '1' && option != '2' ) isValidOption = 0;
    } while(!isValidOption);
    
    /**
     * 1 to watch
     * 2 to come back
    */
    switch (option)
    {
    case ('1'):
        watchMovie(verbosity, user_id, movie.id);
        end = 1;
        break;
    case ('2'):
        break;
    default:
        break;
    }

    if(verbosity) trash = system("clear");
    return end;
}

void printMovieMetadata(Movie movie) {
    printf("Titulo: %s\n", movie.title);
    printf("Ano: %d\n", movie.year);
    printf("Duracao: %d minutos\n", movie.duration);
    printf("Avaliacao: %.2f\n", movie.avaliation);
    printf("Descricao: %s\n", movie.description);
}

void searchMovie(const int verbosity, const int user_id) {
    int inputSize, i, trash, option;
    int movieCount, isValidOption = 1;
    char temp;
    char *input;
    Movie *matches;

    if(verbosity) printf("\t__________________________________\n");
    if(verbosity) printf("\t|                                |\n");
    if(verbosity) printf("\t|    Digite o nome do filme: ");

    inputSize = 10;
    input = (char* ) calloc(inputSize, sizeof(char));
    i = 0;
    /**
     * Loop to get a string that the user is looking for;
    */
    while ((temp = getchar()) != '\n') 
    {
        if(i + 1 == inputSize) 
        {
            inputSize *= 2;
            input = (char* ) realloc(input, inputSize * sizeof(char));
        }

        input[i] = temp;
        input[i + 1] = '\0';
        i++;
    }

    if(verbosity) trash = system("clear");

    if(i == 0) input[0] = '\0';
    matches = getMovieMatches(input, &movieCount);

    free(input);

    if(matches[0].id == -2) 
    {
        if(verbosity) printf("\t__________________________________\n");
        if(verbosity) printf("\t|       Erro ao ler filmes       |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
        if(verbosity) printf("\t|      Digite 1 para voltar      |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
    }
    else if(matches[0].id == -1)
    {
        if(verbosity) printf("\t__________________________________\n");
        if(verbosity) printf("\t|   Nenhum resultado encontrado  |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
        if(verbosity) printf("\t|      Digite 1 para voltar      |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
    }
    else
    {
        if(verbosity) printf("\t__________________________________\n");
        if(verbosity) printf("\t|     Resultados encontrados:    |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
        for(i = 0; i < movieCount; i++) {
            printf("%d- %s\n", matches[i].id, matches[i].title);
        }
        if(verbosity) printf("\t|--------------------------------|\n");
        if(verbosity) printf("\t|      Digite 1 para voltar      |\n");
        if(verbosity) printf("\t|      ou -[ID] pra assistir     |\n");
        if(verbosity) printf("\t|          exemplo: -204         |\n");
        if(verbosity) printf("\t|--------------------------------|\n");
    }
    /**
     * Loop to verify if user's input is a valid entry;
    */
    do {
        if(verbosity) printf("\t|-> ");
        isValidOption = 1;

        while (scanf(" %d", &option) != 1)
        {
            while(getchar() != '\n'){};
            if(verbosity) printf("\t|-> ");
        }
        while(getchar() != '\n'){
            isValidOption = 0;
        };

        if(isValidOption && (option < 0)) {
            for(i = 0; i < movieCount; i++) {
                if((option * -1) == matches[i].id) {
                    isValidOption = 1;
                    break;
                }
                isValidOption = 0;
            }
        }else if(option != 1){
            isValidOption = 0;
        }
    }while(!isValidOption);

    if(option < 0) {
        showMovie(verbosity, matches[i], user_id);
    }

    if(verbosity) trash = system("clear");
    
    for(i = 0; i < movieCount; i++) {
        free(matches[i].title);
        free(matches[i].description);
    }
    free(matches);
}
