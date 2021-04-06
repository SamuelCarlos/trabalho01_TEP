#include "menu.h"
#include "user.h"
#include "movie.h"
#include "watched.h"

void startMenu(const int verbosity){
    int response;
    int verificator = 1;
    int trash;
    char temp;
    char option;

    do{
        if(verbosity){
            printf("\t__________________________\n");
            printf("\t|         UFLIX          |\n");
            printf("\t|------------------------|\n");
            printf("\t|                        |\n");
            printf("\t|       1. Login         |\n");
            printf("\t|       2. Cadastro      |\n");
            printf("\t|       3. Sair          |\n");
            printf("\t|                        |\n");
            printf("\t|------------------------|\n");
            printf("\t| Samuel | v1.0 | Bruno  |\n");
            printf("\t|-------------------------\n");
            printf("\t|-> ");
        }
        if(option = getchar())
        {
            while((temp = getchar()) != '\n'){};
           
            if(verbosity) trash = system("clear");

            switch(option) {
                case('1'):
                    response = signIn(verbosity);
                    if(response > 0) {
                        mainMenu(verbosity, response); 
                    }else if(verbosity){
                        switch (response) {
                            case(-2):
                                if(verbosity) trash = system("clear");
                                
                                printf("\t__________________________\n");
                                printf("\t| Login ou Senha errados |\n");
                                break;
                            case(-1): 
                                if(verbosity) trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t|     Senha incorreta    |\n");
                                break;
                            case(0): 
                                if(verbosity) trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t| Usuario nao cadastrado |\n");
                                break;
                            default: 
                                break;
                        }
                    }
                    break;
                case('2'):
                    response = signUp(verbosity);
                    if(response > 0) {
                        mainMenu(verbosity, response); 
                    }else if(verbosity){
                        switch (response) {
                            case(-3): 
                                if(verbosity) trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t| Senhas nao compativeis |\n");
                                break;
                            case(-2):
                                if(verbosity) trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t|  Usuario ou Senha fora |\n");
                                printf("\t|       do padrao        |\n");
                                break;
                            case(-1):
                                if(verbosity) trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t|  Usuario ja cadastrado |\n");
                                break;
                            default: 
                                break;
                        }
                    }
                    break;
                case('3'):
                    verificator = 0;
                    break;
                default:
                    if(verbosity) printf("Entrada invalida.\n");
                    break;
            }
        }
    }while(verificator);
    createUsuariosFile();
}

void mainMenu(const int verbosity, const int user_id) {
    int response;
    int verificator = 1;
    int trash;
    int deleted = 0;
    char temp;
    char option;

    if(verbosity) trash = system("clear");

    do{
        if(verbosity) printf("\t__________________________________\n");
        if(verbosity) printf("\t|                                |\n");
        if(verbosity) printf("\t|       1. Listar Filmes         |\n");
        if(verbosity) printf("\t|       2. Meu Perfil            |\n");
        if(verbosity) printf("\t|       3. Procurar Filme        |\n");
        if(verbosity) printf("\t|       4. Sair                  |\n");
        if(verbosity) printf("\t|                                |\n");
        if(verbosity) printf("\t|---------------------------------\n");
        if(verbosity) printf("\t|-> ");
        if(option = getchar()){
            while((temp = getchar()) != '\n'){};
           
            if(verbosity) trash = system("clear");

            switch(option) {
                case('1'):
                    listTenMovies(verbosity, user_id);
                    break;
                case('2'):
                    deleted = personalMenu(verbosity, user_id);
                    if(deleted) verificator = 0;
                    break;
                case('3'):
                    searchMovie(verbosity, user_id);
                    break;
                case('4'):
                    verificator = 0;
                    break;
                default:
                    if(verbosity) printf("\t__________________________________\n");
                    if(verbosity) printf("\t|        Entrada invalida        |\n");
                    break;
            }
        }
    }while(verificator);
}

int personalMenu(const int verbosity, const int user_id) {
    int response;
    int verificator = 1;
    int trash;
    char temp;
    char option;

    if(verbosity) trash = system("clear");

    do{
        if(verbosity) printf("\t______________________________\n");
        if(verbosity) printf("\t|                            |\n");
        if(verbosity) printf("\t|       1. Historico         |\n");
        if(verbosity) printf("\t|       2. Excluir conta     |\n");
        if(verbosity) printf("\t|       3. Voltar            |\n");
        if(verbosity) printf("\t|                            |\n");
        if(verbosity) printf("\t|-----------------------------\n");
        if(verbosity) printf("\t|-> ");
        if(option = getchar()){
            while((temp = getchar()) != '\n'){};
           
            if(verbosity) trash = system("clear");

            switch(option) {
                case('1'):
                    showHistory(user_id);
                    break;
                case('2'):
                    deleteUser(user_id);
                    return 1;
                    break;
                case('3'):
                    verificator = 0;
                    break;
                default:
                    if(verbosity) printf("\t______________________________\n");
                    if(verbosity) printf("\t|       Entrada invalida     |\n");
                    break;
            }
        }
    }while(verificator);
}