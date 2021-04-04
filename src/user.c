#include "user.h"

int isAlphanumeric(char c) {
    if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        return 1;
    } else {
        return 0;
    }
}

int signIn() {
    int count = 0;
    int error = 0;
    int userCount;
    char temp;
    char *login, *password;
    User user;

    printf("Login: ");

    login = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if(count > 0) {
                login = (char* ) realloc(login, (count + 1) * sizeof(char));
            }
            login[count] = temp;

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

    if(user.id == -1) {
        free(login);
        return 0;
    }

    free(login);

    printf("Digite a senha: ");

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
    char temp;
    char *login, *password;
    User user;

    printf("Digite o nome do usuario: ");

    login = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if(count > 0) {
                login = (char* ) realloc(login, (count + 1) * sizeof(char));
            }
            login[count] = temp;

            count++;
        }else{
            error = 1;
        }
    }

    if(!count) error = 1;
    login = (char* ) realloc(login, (count + 1) * sizeof(char));
    login[count] = '\0';
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
        user.login = (char* ) calloc(strlen(login), sizeof(char));
        strcpy(user.login, login);
    };
    
    free(login);

    printf("Digite a senha: ");

    password = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            if(count > 0) {
                password = (char* ) realloc(password, (count + 1) * sizeof(char));
            }
            password[count] = temp;
            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    
    password = (char* ) realloc(password, (count + 1) * sizeof(char));
    password[count] = '\0';

    count = 0;

    if(error) {
        free(password);
        free(user.login);
        return -2;
    }

    user.password = (char* ) calloc(strlen(password), sizeof(char));                        
    strcpy(user.password, password);
    free(password);

    printf("Repita a senha: ");

    count = 0;
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
    char *pointer, *token;
    char **row;

    users = fopen("./data/users.csv","r");
    if(users == NULL) {
        user.id = -1;
        return user;
    };
    user.id = 1;

    do {
        // pointer = (char* ) calloc(1, sizeof(char));
        // while((temp = fgetc(users)) != '\n')
        // {
        //     if(temp == EOF) break;
        //     pointer2 = pointer;
        //     if(count > 0) {
        //         pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
        //     }
        //     pointer2[count] = temp;
            
        //     pointer = pointer2;

        //     count++;
        // }
        // count = 0;
        
        // if(temp == EOF){ 
        //     free(pointer);
        //     break;
        // };

        size = 0;
        len = getline(&pointer, &size, users);

        row = (char** ) calloc(3, sizeof(char*));

        token = strtok_r(pointer, ",", &pointer);
        row[array_parser] = token;
        array_parser++;

        while( token != NULL ) {
            if(token == NULL) break;
            token = strtok_r(NULL, ",", &pointer);
            if(array_parser <= 2)
            {
            row[array_parser] = token;
            array_parser++;
            }
        }

        array_parser = 0;

        if(strcmp(value, row[column - 1]) == 0) {
            user.login = (char* ) calloc(strlen(row[0]), sizeof(char));
            strcpy(user.login, row[0]);

            user.password = (char* ) calloc(strlen(row[1]), sizeof(char));
            strcpy(user.password, row[1]);

            user.deleted = atoi(row[2]);

            found = 1;
        }
    
        free(row);

        if(found) break;

        user.id++;
    } while(!found);
    
    *userCount = user.id;
    if(temp == EOF) {
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