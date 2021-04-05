#include "user.h"
#include "utils.h"


int signIn() {
    int count = 0;
    int error = 0;
    int userCount;
    int inputSize;
    char temp;
    char *login, *password;
    User user;

    printf("\t__________________________\n");
    printf("\t|                        |\n");
    printf("\t|        Login: ");

    inputSize = 10;
    login = (char* ) calloc(inputSize, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if((count + 1) == inputSize) {
                inputSize *= 2;
                login = (char* ) realloc(login, inputSize * sizeof(char));
            }

            login[count] = temp;
            login[count + 1] = '\0';

            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    count = 0;
    
    if(error) {
        free(login);
        return -2;
    };

    user = readUserFromFile(1, login, &userCount);
    free(login);

    if(user.id == -1) {
        return 0;
    }

    printf("\t|        Senha: ");

    while((temp = getchar()) != '\n')
    {
        if(user.password[count])
        {
            if(temp != user.password[count]) error = 1;
        }else{
            error = 1;
        }
        count++;
    }
    if(!count) error = 1;
    if(count < strlen(user.password)) error = 1;
    
    count = 0;
    
    free(user.login);
    free(user.password);

    if(error) {
        return -1;
    }

    return user.id;

}

int signUp() {  
    int count = 0;
    int error = 0;
    int userCount;
    int inputSize;
    char temp;
    char *login, *password;
    User user;

    printf("\t__________________________\n");
    printf("\t|                        |\n");
    printf("\t|    Digite o nome       |\n");
    printf("\t|       do usuario: ");

    inputSize = 10;
    login = (char* ) calloc(inputSize, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if((count + 1) == inputSize) {
                inputSize *= 2;
                login = (char* ) realloc(login, inputSize * sizeof(char));
            }
            login[count] = temp;
            login[count + 1] = '\0';

            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    count = 0;

    if(error) {
        free(login);
        return -2;
    };
    
    user = readUserFromFile(1, login, &userCount);

    if(user.id > 0) {
        free(login);
        return -1;
    }

    if(user.id == -1) {
        user.id = userCount;
        user.login = (char* ) calloc(strlen(login) + 1, sizeof(char));
        strcpy(user.login, login);
        user.login[strlen(login) + 1] = '\0';
    };
    
    free(login);

    printf("\t|   Digite a senha: ");


    inputSize = 10;
    password = (char* ) calloc(inputSize, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if((count + 1) == inputSize) {
                inputSize *= 2;
                password = (char* ) realloc(password, inputSize * sizeof(char));
            }
            password[count] = temp;
            password[count + 1] = '\0';
            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    count = 0;

    if(error) {
        free(password);
        free(user.login);
        return -2;
    }

    user.password = (char* ) calloc(strlen(password) + 1, sizeof(char));                        
    strcpy(user.password, password);
    user.password[strlen(password) + 1] = '\0';
    free(password);

    printf("\t|   Repita a senha: ");

    while((temp = getchar()) != '\n')
    { 
        if(user.password[count]){
            if(temp != user.password[count]) error = 1;
        }else{
            error = 1;
        }
        count++;
    }

    if(count < strlen(user.password)) error = 1;
    if(error) {
        free(user.login);
        free(user.password);
        return -3;
    }   

    user.deleted = 0;

    writeUserOnFile(user);

    return user.id;
}   

User readUserFromFile(int column, char *value, int *userCount) {
    FILE *users;
    User user;
    int i, len;
    int count = 0, found = 0, array_parser = 0;
    long unsigned int size;
    char temp;
    char *pointer, *pointer2, *token;
    char **row;

    users = fopen("./data/users.csv","r");
    if(users == NULL) {
        user.id = -1;
        return user;
    };
    user.id = 1;

    do {
        size = 0;
        len = getline(&pointer, &size, users);
        if(len == -1)
        {
            free(pointer); 
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;

        row = (char** ) calloc(3, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        while( token != NULL ) {
            if(token == NULL) 
            {
                free(row);
                break;
            }
            token = strtok_r(NULL, ",", &pointer);
            if(array_parser <= 2)
            {
            row[array_parser] = token;
            array_parser++;
            }
        }

        array_parser = 0;

        if(strcmp(value, row[column - 1]) == 0) {
            user.login = (char* ) calloc(strlen(row[0]) + 1, sizeof(char));
            user.login = strdup(row[0]);

            user.password = (char* ) calloc(strlen(row[1]) + 1, sizeof(char));
            user.password = strdup(row[1]);

            user.deleted = atoi(row[2]);

            found = 1;
        }
    
        free(row);
        free(pointer2);
        if(found) break;

        user.id++;
    } while(!found);


    *userCount = user.id;
    if(!found) {
        user.id = -1;
    }

    fclose(users);
    return user;
}

void writeUserOnFile(User user){
    FILE *users;
    users = fopen("./data/users.csv","a");
    
    fprintf(users, "%s,%s,%d\n", user.login, user.password, user.deleted);

    free(user.login);
    free(user.password);
    fclose(users);
}