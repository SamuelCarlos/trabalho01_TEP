#include "user.h"
#include "utils.h"
#include "watched.h"

int signIn(const int verbosity) {
    int count = 0;
    int error = 0;
    int userCount;
    int inputSize;
    char temp;
    char *login, *password;
    User user;

    if(verbosity) printf("\t__________________________\n");
    if(verbosity) printf("\t|                        |\n");
    if(verbosity) printf("\t|        Login: ");

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

    if(user.id == -2) {
        if(createUsersFile() == -1) {
            user.id = -1;
        }else{
            user = readUserFromFile(1, login, &userCount);
        }
    }

    free(login);

    if(user.id == -1) {
        return 0;
    }


    if(verbosity) printf("\t|        Senha: ");

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

int signUp(const int verbosity) {  
    int count = 0;
    int error = 0;
    int userCount;
    int inputSize;
    char temp;
    char *login, *password;
    User user;

    if(verbosity) printf("\t__________________________\n");
    if(verbosity) printf("\t|                        |\n");
    if(verbosity) printf("\t|    Digite o nome       |\n");
    if(verbosity) printf("\t|       do usuario: ");

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

    if(verbosity) printf("\t|   Digite a senha: ");


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

    if(verbosity) printf("\t|   Repita a senha: ");

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
        user.id = -2;
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

        if(strcmp(value, row[column - 1]) == 0 && atoi(row[2]) == 0) {
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

User getUserById(const int id) {
    FILE *users;
    User user;
    int i, found = 0, array_parser = 0, len, length;
    long unsigned int size;
    char *pointer, *pointer2, *token;
    char **row;

    users = fopen("./data/users.csv","r");
    if (users == NULL) {
        user.id = -2;
        return user;
    }

    user.id = 1;

    do {
        size = 0;
        len = getline(&pointer, &size, users);
        if(len == -1){
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;

        if(user.id == id) {

            row = (char** ) calloc(3, sizeof(char*));

            token = strtok_r(pointer, ",", &pointer);
            row[array_parser] = token;
            array_parser++;

            for(i = 1; i < 3; i++) {
                if(token == NULL) break;
                token = strtok_r(NULL, ",", &pointer);
                row[array_parser] = token;
                array_parser++;
            }
            array_parser = 0;

            length = strlen(row[0]) + 1;
            user.login = (char* ) calloc(length, sizeof(char));
            user.login = strdup(row[0]);

            length = strlen(row[1]) + 1;
            user.password = (char* ) calloc(length, sizeof(char));
            user.password = strdup(row[1]);

            user.deleted = atoi(row[2]);
        
            found = 1;
            free(row);
        }
     
        free(pointer2);
        if(found) break;

        user.id++;
    } while(!found);
 
    if(!found) {
        user.id = -1;
    }
    fclose(users);
    return user;
}

void writeUserOnFile(User user) {
    FILE *users;
    users = fopen("./data/users.csv","a");
    
    fprintf(users, "%s,%s,%d\n", user.login, user.password, user.deleted);

    free(user.login);
    free(user.password);
    fclose(users);
}

void deleteUser(int user_id) {
    FILE *users;
    User user;
    int found = 0, len;
    long unsigned int size;
    char *pointer, *pointer2;

    users = fopen("./data/users.csv","r+");

    user.id = 1;

    do {
        size = 0;
        len = getline(&pointer, &size, users);
        if(len == -1){
            free(pointer);
            break;
        }
        pointer[len] = '\0';

        pointer2 = pointer;

        if(user.id == user_id) {
            
            fseek( users, -2, SEEK_CUR );
            fputc('1', users);
        
            found = 1;
        }
     
        free(pointer2);
        if(found) break;

        user.id++;
    } while(!found);
    
    fclose(users);
}

void createUsuariosFile() {
    FILE *users;
    FILE *allWatched;
    FILE *usuarios;
    User user;
    Watched *history;
    int usersLen, watchedLen, i, manyWatched;
    long unsigned int usersSize, watchedSize;
    char *usersPointer, *usersPointer2, *watchedPointer, *watchedPointer2, *token;
    char **row;

    usuarios = fopen("./data/usuarios.csv", "w");
    allWatched = fopen("./data/watched.csv", "r");
    users = fopen("./data/users.csv","r");

    user.id = 1;

    do {
        usersSize = 0;
        usersLen = getline(&usersPointer, &usersSize, users);
        if(usersLen == -1){
            free(usersPointer);
            break;
        } 
        usersPointer[usersLen] = '\0';

        usersPointer2 = usersPointer;

        row = (char**) calloc(2, sizeof(char*));

        i = 0;

        token = strtok_r(usersPointer, ",", &usersPointer);
        row[i] = token;

        for(i = 1; i < 3; i++) 
        {
            if(token == NULL) break;
            token = strtok_r(NULL, ",", &usersPointer);
            row[i] = token;
        }

        if(atoi(row[2]) == 0) 
        {
            fprintf(usuarios, "%s,%s", row[0], row[1]);
            history = getUserHistory(user.id, &manyWatched);

            if(history[0].id > 0) 
            {
                for(i = 0; i < manyWatched; i++) 
                {
                    fprintf(usuarios, ",%d,%.2f,%.2d/%.2d/%.4d", history[i].movie_id, history[i].user_avaliation, history[i].day, history[i].month, history[i].year);
                }
            }

            free(history);
            fprintf(usuarios, "\n");
        }

        free(row);
        free(usersPointer2);

        user.id++;
    } while(1);

    fclose(users);
    fclose(allWatched);
    fclose(usuarios);
}

int createUsersFile() {
    FILE *users;
    FILE *usuarios;
    int usersLen, i;
    long unsigned int usersSize;
    char *usersPointer;

    users = fopen("./data/users.csv","w");
    usuarios = fopen("./data/usuarios.csv", "r");
    if(usuarios == NULL) {
        fclose(users);
        return -1;
    }

    do {
        usersSize = 0;
        usersLen = getline(&usersPointer, &usersSize, usuarios);
        if(usersLen == -1){
            free(usersPointer);
            break;
        } 
        usersPointer = (char* ) realloc(usersPointer, (usersLen + 1) * sizeof(char));
        usersPointer[usersLen - 1] = ',';
        usersPointer[usersLen] = '0';
        usersPointer[usersLen + 1] = '\n';

        fprintf(users, "%s", usersPointer);
        
        free(usersPointer);
    } while(1);

    fclose(users);
    fclose(usuarios);
    return 0;
}