#include "user.h"

int isAlphanumeric(char c) {
    if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
        return 1;
    } else {
        return 0;
    }
}

int signIn() {
    return -1;
}

int signUp() {  
    int count = 0;
    int error = 0;
    int userCount;
    char temp;
    char *pointer, *pointer2;
    User user;

    printf("Digite o nome do usuario: ");
    getchar();

    pointer = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;

            pointer = pointer2;

            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    count = 0;

    if(error) {
        free(pointer);
        return -2;
    };

    printf("name: %s\n", pointer);
    
    user = readUserFromFile(1, pointer, &userCount);

    if(user.id > 0) {
        free(pointer);
        return -1;
    }

    if(user.id == -1) {
        user.id = userCount;
        user.login = (char* ) calloc(strlen(pointer), sizeof(char));
        strcpy(user.login, pointer);
    };

    free(pointer);

    printf("Digite a senha: ");

    pointer = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    {
        if(isAlphanumeric(temp)) {
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;
            pointer = pointer2;
            count++;
        }else{
            error = 1;
        }
    }
    if(!count) error = 1;
    count = 0;

    if(error) {
        free(pointer);
        free(user.login);
        return -2;
    }

    user.password = (char* ) calloc(strlen(pointer), sizeof(char));                         // FREE IT!
    printf("teste de senha: %s\n", pointer);
    strcpy(user.password, pointer);
    free(pointer);

    printf("Repita a senha: ");

    pointer = (char* ) calloc(1, sizeof(char));
    while((temp = getchar()) != '\n')
    { 
        pointer2 = pointer;
        if(count > 0) {
            pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
        }
        pointer2[count] = temp;
        pointer = pointer2;
        count++;
    }

    printf("digite a senha: %s\nrepita a senha: %s\n", user.password, pointer);

    if(strcmp(user.password, pointer) != 0) {
        free(pointer);
        free(user.login);
        free(user.password);
        return -3;
    }   

    user.deleted = 0;

    printf("ID: %d\nLOGIN: %s\nPASSWORD: %s\nDELETED: %d\n", user.id, user.login, user.password, user.deleted);

    writeUserOnFile(user);

    free(pointer);

    return user.id;
}   

User readUserFromFile(int column, char *value, int *userCount) {
    FILE *users;
    int i;
    int count = 0, found = 0, array_parser = 0;
    char temp;
    char *pointer, *pointer2, *token;
    char **row;
    User user;

    users = fopen("./data/users.csv","r");
    if(users == NULL) {
        user.id = -1;
        return user;
    };
    user.id = 1;


    do {
        pointer = (char* ) calloc(1, sizeof(char));
        while((temp = fgetc(users))!= '\n')
        {
            if(temp == EOF) break;
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;
            
            pointer = pointer2;

            count++;
        }
        count = 0;
        
        if(temp == EOF){ 
            free(pointer);
            break;
        };

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
            user.login = row[0];
            user.password = row[1];
            user.deleted = atoi(row[2]);
            found = 1;
        }

        free(row);
        free(pointer2);

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