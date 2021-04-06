#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int id;           // user id (from 1 to infinite)
    char *login;
    char *password;
    int deleted;      // user delete data (0: not deleted, 1: deleted)
} User;


/*
@brief query the users file searching for a specific column value
example: login, password, deleted as 1, 2, 3 respectively;
@param int column: id for the specific column you want to query;
@param char *value: string who contains the value to be queried;
@return User struct with user data, or an empty User struct with
only User.id as -1 who indicates that the user don't exist;
*/
User readUserFromFile(int column, char *value, int *userCount);

/*
@brief query the users file searching for a user by his ID;
@param int column: id for the specific column you want to query;
@param char *value: string who contains the value to be queried;
@return User struct with user data, or an empty User struct with
only User.id as -1 who indicates that the user don't exist;
*/
User getUserById(const int id);

/*
@brief organizate the sign-in process nesting all funcionalities
needed to login an user;
@return -2: error    (login or password impossible); 
        -1: conflict (wrong password); 
         0: null     (not existent user);
        >0: user id  (actual user);
*/
int signIn(const int verbosity);

/*
@brief organizate the sign-up process nesting all funcionalities
needed to create a new user account;
@param const int verbosity: defines if menus are about to be printed;
@return -3: error    (wrong password repeating);
        -2: error    (unexpected login or password model);
        -1: conflict (already existent user);
        >0: user id  (actual user);
*/
int signUp(const int verbosity);


/*
@brief query users file and write a new user on last position;
@param User user: User struct who contains the actual user data;
*/
void writeUserOnFile(User user);

/*
@brief query users file and modify "deleted" correspondent column
with "1" value;
@param const int user_id: user id key for querying at users file;
*/
void deleteUser(const int user_id);

/*
@brief create a new Usuarios file and write on it not deleted users
and they history. It queries users and watched files to catch data;
*/
void createUsuariosFile();

#endif //user_h