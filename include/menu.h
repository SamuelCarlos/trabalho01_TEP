#ifndef MENU_H
#define MENU_H


/*
@brief once user is logged through "startMenu", he will be
redirected to this.
@param const int verbosity: defines menus are going to be printed;
@param const int user_id: the ID of the logged user, it can't be
changed;
*/
void mainMenu(const int verbosity, const int user_id);

/*
@brief makes the login, logon and logout works. Once logged, it
redirects the user to "mainMenu", otherwise, it keeps user at this
menu until he log or quit;
@param const int verbosity: defines menus are going to be printed;
*/
void startMenu(const int verbosity);

/*
@brief this shows up options to user track his own data, as his
history or deleting his account;
@param const int verbosity: defines menus are going to be printed;
@param const int user_id: the ID of the logged user, it can't be
changed;
@return 1: user deleted;
        0: not deleted;
*/
int personalMenu(const int verbosity, const int user_id);

#endif //menu_h