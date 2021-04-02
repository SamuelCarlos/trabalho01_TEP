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
    while(scanf("%c", &temp) != '\n')
    {
        if(isAlphanumeric(temp)) {
            pointer = (char* ) calloc(1, sizeof(char));
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;

            pointer = pointer2;
            free(pointer2);

            count++;
        }else{
            error = 1;
        }
    }
    count = 0;

    if(error) {
        free(pointer);
        return -2;
    };
    
    user = readUserFromFile(1, pointer, &userCount);
    if(user.id == -1) {
        user.id = userCount;
        user.login = pointer;
    };
    free(pointer);

    if(user.id > 0) {
        free(user.login);
        free(user.password);
        return -1;
    }

    printf("Digite a senha: ");

    while(scanf("%c", &temp) != '\n')
    {
        if(isAlphanumeric(temp)) {
            pointer = (char* ) calloc(1, sizeof(char));
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;

            free(pointer);
            pointer = pointer2;
            free(pointer2);

            count++;
        }else{
            error = 1;
        }
    }
    count = 0;

    if(error) {
        free(pointer);
        return -2;
    }

    user.password = pointer;
    free(pointer);

    while(scanf("%c", &temp) != '\n')
    {
        if(isAlphanumeric(temp)) {
            pointer = (char* ) calloc(1, sizeof(char));
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;

            free(pointer);
            pointer = pointer2;
            free(pointer2);

            count++;
        }else{
            error = 1;
        }
    }
    count = 0;

    if(strcmp(user.password, pointer) != 0) {
        free(user.login);
        free(user.password);
        return -3;
    }

    writeUserOnFile(user);

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
        while(fscanf(users, "%c", &temp) != '\n')
        {
            if(temp == EOF) break;
            pointer = (char* ) calloc(1, sizeof(char));
            pointer2 = pointer;
            if(count > 0) {
                pointer2 = (char* ) realloc(pointer2, (count + 1) * sizeof(char));
            }
            pointer2[count] = temp;

            free(pointer);
            pointer = pointer2;
            free(pointer2);

            count++;
        }
        count = 0;
        
        if(temp == EOF) break;

        row = (char** ) calloc(3, sizeof(char*));

        token = strtok(pointer, ",");
        row[array_parser] = token;
        array_parser++;

        while( token != NULL ) {
            token = strtok(NULL, ",");
            row[array_parser] = token;
            array_parser++;
        }

        free(token);
        free(pointer);
        array_parser = 0;

        if(strcmp(value, row[column]) == 0) {
            user.login = row[0];
            user.password = row[1];
            user.deleted = atoi(row[2]);
            found = 1;
        }

        for (i = 0; i < 3; i++){
            free(row[i]);
        }
        free(row);

        user.id++;
    } while(!found);
    
    if(temp == EOF) {
        user.id = -1;
    }

    fclose(users);
    *userCount = user.id;
    return user;
}

void writeUserOnFile(User user){
    FILE *users;
    users = fopen("./data/users.csv","w");
    
    fprintf(users, "%s,%s,%d\n", user.login, user.password, user.deleted);

    free(user.login);
    free(user.password);
    fclose(users);
}