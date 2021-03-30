#ifndef USER_H
#define USER_H

typedef struct {
    int id;           // user id (from 1 to infinite)
    char *login;
    char *password;
    char *deleted_at; // user delete date
} User;


User createNewUser(char *login, char *password);

User readUserFromFile(int column, char *value);

int signIn();

int signUp();

void writeUserOnFile(User *user);

void deleteUser(int user_id);

#endif //user_h