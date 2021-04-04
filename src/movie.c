#include "movie.h"
#include "watched.h"

int isNumber(char c) {
    if (c >= '0' && c <= '9'){ 
        return 1; 
    } else {
        return 0;
    }
}

void listTenMovies(int user_id)
{
    int end = 0, i, j = 0;
    int error = 0;
    int trash;
    int movieQnt;
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
            movies = (Movie* ) calloc(1, sizeof(Movie));
            j = 0;
            movieQnt = 0;

            for (i = (actualPage * 10 + 1); i < (actualPage + 1) * 10; i++) 
            {
                if(movieQnt > 0){
                    movies = (Movie* ) realloc(movies, (j + 1) * sizeof(Movie));
                }
                movies[j] = getMovieByID(i);

                // printf("Pegou o filme: %d\n", movie.id);

                if(movies[j].id == -2) {
                    printf("Erro ao ler arquivo.\n");
                    error = 1;
                    break;
                }
                if(movies[j].id == -1){
                    end = 1;
                    break;
                }

                // printf("ALOCOU CERTINHO O FILME: %d\n", movies[j].id);
                movieQnt++;
                j++;
            }
            if(error) break;

            printf("_____________________________________________________\n");

            for (i = 0; i < movieQnt; i++){
                printf("| %d  |   %s\n", movies[i].id, movies[i].title);
            }

            printf("_____________________________________________________\n");

            if(actualPage > 0 && !end) {
                printf("| < A |           voltar ao menu: 0           | M > |\n");
            }else if (actualPage == 0 && !end){
                printf("|                 voltar ao menu: 0           | M > |\n");
            }else if(actualPage > 0 && end) {
                printf("| < A |           voltar ao menu: 0                 |\n");
            }else if(actualPage == 0 && end) {
                printf("|                 voltar ao menu: 0                 |\n");
            }
            printf("-----------------------------------------------------\n");

            printf("Escolha seu filme ou navegue pelas paginas: ");

            do {
                if(!isValidOption){
                    printf("Digite uma opcao valida: ");
                    isValidOption = 1;  
                }
                option = (char* ) calloc(1, sizeof(char));
                i = 0;
                while((temp = getchar()) != '\n'){
                    if(!isNumber(temp) && i > 0) isValidOption = 0;
        
                    option[i] = temp;
                    i++;
                    option = (char* ) realloc(option, (i + 1) * sizeof(char));
                }
            } while(!isValidOption);

            if(strcmp(option, "A") == 0 && actualPage > 0) {
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
                    end = showMovie(movies, optionNumber, user_id);
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
    int i;
    int count = 0, found = 0, array_parser = 0, len;
    long unsigned int size;
    char temp;
    char *pointer, *token;
    char **row;

    movies = fopen("./data/movies.csv","r");
    if (movies == NULL) {
        movie.id = -2;
        return movie;
    }

    movie.id = 1;

    do {
        // pointer = (char* ) calloc(1, sizeof(char));
        // while((temp = fgetc(movies)) != '\n')
        // {
        //     if(temp == EOF) break;
           
        //     if(count > 0) {
        //         pointer = (char* ) realloc(pointer, (count + 1) * sizeof(char));
        //     }
        //     pointer[count] = temp;

        //     pointer2 = pointer;

        //     count++;
        // }
        // pointer = (char* ) realloc(pointer, (count + 1) * sizeof(char));
        // pointer[count] = '\0';
        // count = 0;

        // if(temp == EOF){ 
        //     free(pointer2);
        //     break;
        // };

        size = 0;
        len = getline(&pointer, &size, movies);

        printf("%li\n", size);

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

            movie.title = (char* ) calloc(strlen(row[0]), sizeof(char));
            strcpy(movie.title, row[0]);

            movie.year = atoi(row[1]);
            movie.duration = atoi(row[2]);
            movie.avaliation = atof(row[3]);

            movie.description = (char* ) calloc(strlen(row[4]), sizeof(char));
            strcpy(movie.description, row[4]);

            free(row);
            found = 1;
        }

        if(found) break;

        movie.id++;
    } while(!found);
    
    if(temp == EOF) {
        movie.id = -1;
    }
    fclose(movies);
    return movie;
}

int showMovie(Movie* movies, int optionNumber, int user_id) {
    Movie movie;
    int i = 0, trash, end = 0;
    int isValidOption = 1;
    char temp;
    char* option;

    movie = movies[(optionNumber % 10) - 1];
            printMovieMetadata(movie);
            printf("O que deseja fazer?\n1: Assistir\n2: Voltar\n");

            do {
                if(!isValidOption){
                    printf("Digite uma opcao valida: ");
                    isValidOption = 1;  
                }
                option = (char* ) calloc(1, sizeof(char));
                i = 0;
                while((temp = getchar()) != '\n'){
                    if(!isNumber(temp) && i > 0) isValidOption = 0;
        
                    option[i] = temp;
                    i++;
                    option = (char* ) realloc(option, (i + 1) * sizeof(char));
                }
            } while(!isValidOption);

            printf("option: %s\n", option);

          
            optionNumber = atoi(option);
            switch (optionNumber)
            {
            case (1):
                watchMovie(user_id, movie.id);
                printf("assistido");
                end = 1;
                break;
            case (2):
                    
                break;
            default:
                break;
            }

            free(option);
            trash = system("clear");
            return end;
}

void printMovieMetadata(Movie movie) {
    printf("Titulo: %s\nAno: %d\nDuracao (min): %d\nNota: %.1f\nDescricao: %s\n\n", movie.title, movie.year, movie.duration, movie.avaliation, movie.description);
}

void watchMovie(int user_id, int movie_id) {
    int day, month, year;
    char temp;
    float user_avaliation;

    printf("Digite sua nota para o filme: ");
    while(!scanf(" %f\n", &user_avaliation)){
        printf("Digite uma nota no formato x.x: ");
    };
    
    printf("Data de quando assistiu.\n");
    do{
        printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        while(scanf("%d/%d/%d\n", &day, &month, &year) != 3){
            printf("Digite uma data valida e no formato (dd/mm/aaaa): ");
        } 
    }while(!verifyValidDate(day, month, year));


}

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
