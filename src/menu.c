#include "menu.h"
#include "user.h"
#include "movie.h"

void startMenu(){
    int response;
    int verificator = 1;
    int trash;
    char temp;
    char option;

    do{
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
        if(option = getchar())
        {
            while((temp = getchar()) != '\n'){};
           
            trash = system("clear");

            switch(option) {
                case('1'):
                    response = signIn();
                    if(response > 0) {
                        mainMenu(response); 
                        verificator = 0;
                    }else{
                        switch (response) {
                            case(-2):
                                trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t| Login ou Senha errados |\n");
                                break;
                            case(-1): 
                                trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t|     Senha incorreta    |\n");
                                break;
                            case(0): 
                                trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t| Usuario nao cadastrado |\n");
                                break;
                            default: 
                                break;
                        }
                    }
                    break;
                case('2'):
                    response = signUp();
                    if(response > 0) {
                        mainMenu(response); 
                        verificator = 0;
                    }else{
                        switch (response) {
                            case(-3): 
                                trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t| Senhas nao compativeis |\n");
                                break;
                            case(-2):
                                trash = system("clear");
                                printf("\t__________________________\n");
                                printf("\t|  Usuario ou Senha fora |\n");
                                printf("\t|       do padrao        |\n");
                                break;
                            case(-1):
                                trash = system("clear");
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
                    printf("Entrada invalida.\n");
                    break;
            }
        }
    }while(verificator);
}

void mainMenu(int user_id) {
    int response;
    int verificator = 1;
    int trash;
    char temp;
    char option;

    trash = system("clear");

    do{
        printf("\t__________________________________\n");
        printf("\t|                                |\n");
        printf("\t|       1. Listar Filmes         |\n");
        printf("\t|       2. Meu Perfil            |\n");
        printf("\t|       3. Procurar Filme        |\n");
        printf("\t|       4. Sair                  |\n");
        printf("\t|                                |\n");
        printf("\t|---------------------------------\n");
        printf("\t|-> ");
        if(option = getchar()){
            while((temp = getchar()) != '\n'){};
           
            trash = system("clear");

            switch(option) {
                case('1'):
                    listTenMovies(user_id);
                    break;
                case('2'):
                    personalMenu(user_id);
                    break;
                case('3'):
                    searchMovie(user_id);
                    break;
                case('4'):
                    verificator = 0;
                    break;
                default:
                    printf("\t__________________________________\n");
                    printf("\t|        Entrada invalida        |\n");
                    break;
            }
        }
    }while(verificator);
}

void personalMenu(int user_id) {
    int response;
    int verificator = 1;
    int trash;
    char temp;
    char option;

    trash = system("clear");

    do{
        printf("\t______________________________\n");
        printf("\t|                            |\n");
        printf("\t|       1. Historico         |\n");
        printf("\t|       2. Excluir conta     |\n");
        printf("\t|       3. Voltar            |\n");
        printf("\t|                            |\n");
        printf("\t|-----------------------------\n");
        printf("\t|-> ");
        if(option = getchar()){
            while((temp = getchar()) != '\n'){};
           
            trash = system("clear");

            switch(option) {
                case('1'):
                    break;
                case('2'):
                    break;
                case('3'):
                    verificator = 0;
                    break;
                default:
                    printf("\t______________________________\n");
                    printf("\t|       Entrada invalida     |\n");
                    break;
            }
        }
    }while(verificator);
}