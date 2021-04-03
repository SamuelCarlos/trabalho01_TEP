#include "menu.h"
#include "user.h"

void startMenu(){
    int option, response;
    int verificator = 1;
    int trash;

    do{
        printf("1. Login\n2. Cadastro\n3. Sair\n");
        if(option = getchar()){
            getchar();
           
            trash = system("clear");

            switch(option) {
                case('1'):
                    response = signIn();
                    if(response > 0) {
                        mainMenu(response); 
                        verificator = 0;
                    }else{
                        switch (response) {
                            case(-1): 
                                printf("Senha incorreta.\n");
                                break;
                            case(0): 
                                printf("Usuario nao cadastrado.\n");
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
                                printf("Senhas nao compativeis.\n");
                                break;
                            case(-2):
                                printf("Usuario ou Senha fora do padrao.\n");
                                break;
                            case(-1):
                                printf("Usuario ja cadastrado.\n");
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
    printf("%d", user_id);
}