#include "movie.h"
#include "watched.h"
#include "utils.h"


void listTenMovies(int user_id)
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
        do {
            movies = (Movie* ) calloc(10, sizeof(Movie));
            j = 0;
            movieQnt = 0;

            for (i = (actualPage * 10 + 1); i < (actualPage + 1) * 10; i++) 
            {
                movies[j] = getMovieByID(i);


                if(movies[j].id == -2) {
                    printf("Erro ao ler arquivo.\n");
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
            
            printf("_____________________________________________________\n");
            printf("|  ID |   Titulo                                    |\n"); 
            printf("|-----|---------------------------------------------|\n");

            for (i = 0; i < movieQnt; i++){
                printf("| %d  |   %s\n", movies[i].id, movies[i].title);
            }

            printf("______|______________________________________________\n");

            if((actualPage > 0) && !end) {
                printf("| < A |           voltar ao menu: 0           | M > |\n");
            }else if ((actualPage == 0) && !end){
                printf("|                 voltar ao menu: 0           | M > |\n");
            }else if((actualPage > 0) && end) {
                printf("| < A |           voltar ao menu: 0                 |\n");
            }else if((actualPage == 0) && end) {
                printf("|                 voltar ao menu: 0                 |\n");
            }
            printf("-----------------------------------------------------\n");

            printf("Escolha seu filme ou navegue pelas paginas: ");

            do {
                if(!isValidOption){
                    printf("Digite uma opcao valida: ");
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
            }else if(strcmp(option, "0") == 0){
                end = 1;
                verificator = 0;
            }else if(strlen(option) >= 1 && isNumber(option[0])){
                optionNumber = atoi(option);
                if ((optionNumber >= (actualPage * 10 + 1)) && (optionNumber < (actualPage + 1) * 10)) {
                    verificator = 0;

                    trash = system("clear");
                    end = showMovie(movies[(optionNumber % 10) - 1], user_id);
                }
            }

            for(i = 0; i < movieQnt; i++){
                free(movies[i].title);
                free(movies[i].description);
            }

            free(movies);
            free(option);

            trash = system("clear");
        }while (verificator);

        verificator = 1;

        if(error) break;

    } while (!end);
}

Movie getMovieByID(int id)
{
    FILE *movies;
    Movie movie;
    int i, found = 0, array_parser = 0, len, length;
    long unsigned int size;
    char *pointer, *pointer2, *token;
    char **row;

    movies = fopen("./data/movies.csv","r");
    if (movies == NULL) {
        movie.id = -2;
        return movie;
    }

    movie.id = 1;

    do {
        size = 0;
        len = getline(&pointer, &size, movies);
        if(len == -1){
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;

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

    movies = fopen("./data/movies.csv","r");

    matches = (Movie* ) calloc((count + 1) , sizeof(movie));

    if (movies == NULL) {
        matches[0].id = -2;
        return matches;
    }

    movie.id = 1;
    *movieCount = 1; 

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

    *movieCount = count;

    fclose(movies);
    return matches;
}

int showMovie(Movie movie, int user_id) {
    int i = 0, trash, end = 0;
    int isValidOption = 1;
    int optionSize;
    int optionNumber;
    char temp;
    char* option;
  
    printMovieMetadata(movie);
    printf("\t               O que deseja fazer?\n\n\t               1: Assistir\n\t               2: Voltar\n\t            -> ");

    do {
        if(!isValidOption)
        {
            printf("Digite uma opcao valida: ");
            isValidOption = 1;  
        }

        optionSize = 10;
        option = (char* ) calloc(optionSize, sizeof(char));
        i = 0;
        while((temp = getchar()) != '\n')
        {
            if(!isNumber(temp)) isValidOption = 0;
            if((i + 1) == optionSize) 
            {
                optionSize *= 2;
                option = (char* ) realloc(option, optionSize * sizeof(char));
            }
            option[i] = temp;
            option[i + 1] = '\0';
            i++;
        }
    } while(!isValidOption);

    optionNumber = atoi(option);
    free(option);
    
    switch (optionNumber)
    {
    case (1):
        watchMovie(user_id, movie.id);
        end = 1;
        break;
    case (2):
                    
        break;
    default:
        break;
    }

    trash = system("clear");
    return end;
}

void printMovieMetadata(Movie movie) {
    printf("\n\t       Titulo: %s\n", movie.title);
    printf("\t          Ano: %d\n", movie.year);
    printf("\t      Duracao: %d min\n", movie.duration);
    printf("\t         Nota: %.2f\n", movie.avaliation);
    printf("\t    Descricao: %s\n", movie.description);
}

void watchMovie(int user_id, int movie_id) {
    int isValidOption = 1, i = 0;
    int optionSize;
    char temp;
    char *option;
    Watched watched;

    watched.user_id = user_id;
    watched.movie_id = movie_id;

    printf("Digite sua nota para o filme: ");
    do {
        if(!isValidOption)
        {
            printf("Digite uma opcao valida: ");
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

    watched.user_avaliation = atof(option);

    free(option);

    printf("Data de quando assistiu.\n");
    do{
        printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        while(scanf("%d/%d/%d", &watched.day, &watched.month, &watched.year) != 3){
            getchar();
            printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        } 
        getchar();
    }while(!verifyValidDate(watched.day, watched.month, watched.year));

    writeNewWatched(watched);
}

void searchMovie(int user_id) {
    int inputSize, i, trash;
    int movieCount, isValidOption = 1;
    char temp;
    char *input;
    Movie *matches;

    printf("\t__________________________________\n");
    printf("\t|                                |\n");
    printf("\t|    Digite o nome do filme: ");

    inputSize = 10;
    input = (char* ) calloc(inputSize, sizeof(char));
    i = 0;
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

    trash = system("clear");

    matches = getMovieMatches(input, &movieCount);

    free(input);

    if(matches[0].id == -2) 
    {
        printf("\t__________________________________\n");
        printf("\t|       Erro ao ler filmes       |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|      Digite 1 para voltar      |\n");
        printf("\t|--------------------------------|\n");
    }
    else if(matches[0].id == -1)
    {
        printf("\t__________________________________\n");
        printf("\t|   Nenhum resultado encontrado  |\n");
        printf("\t|--------------------------------|\n");
        printf("\t|      Digite 1 para voltar      |\n");
        printf("\t|--------------------------------|\n");
    }
    else
    {
        printf("\t__________________________________\n");
        printf("\t|     Resultados encontrados:    |\n");
        printf("\t|--------------------------------|\n");
        for(i = 0; i < movieCount; i++) {
            printf("\t| %d |   %s\n", matches[i].id, matches[i].title);
        }
        printf("\t|--------------------------------|\n");
        printf("\t|    Digite o ID do filme ou     |\n");
        printf("\t|         1 para voltar:         |\n");
        printf("\t|--------------------------------|\n");
    }

    do {
        printf("\t|-> ");
        isValidOption = 1;
        inputSize = 10;
        input = (char* ) calloc(inputSize, sizeof(char));
        i = 0;
        while ((temp = getchar()) != '\n') 
        {
            if(i + 1 == inputSize) 
            {
                inputSize *= 2;
                input = (char* ) realloc(input, inputSize * sizeof(char));
            }

            if(!isAlphanumeric(temp)) isValidOption = 0;
            if(isAlphanumeric(temp) && !isNumber(temp)) isValidOption = 0;

            input[i] = temp;
            input[i + 1] = '\0';
            i++;
        }
        if(!input[0]) isValidOption = 0;
        
        if(!isValidOption) 
        {
            free(input);
        }
    }while(!isValidOption);

    trash = system("clear");
    switch(atoi(input)) {
        case (1):
            break;
        default:
            for(i = 0; i < movieCount; i++){
                if(matches[i].id == atoi(input)) 
                {
                    showMovie(matches[i], user_id);
                    break;
                }
            }
            break;
    }
    for(i = 0; i < movieCount; i++) {
        free(matches[i].title);
        free(matches[i].description);
    }
    free(matches);
    free(input);
}
