# :computer: UFLIX :cinema: 

:smile: Welcome to UFLIX project page.

:rocket: UFLIX is an application made in C language by 2 Computer Science students from Ufes (Universidade Federal do Espírito Santo) as a "Topicos Especiais de Programação I" coursework.

> [Bruno Carneiro Izoton](https://github.com/brunoizoton2001)
> [Samuel Carlos Xavier de Carvalho](https://github.com/SamuelCarlos)

## What is UFLIX: 

:desktop_computer: It's an application where user can sign up and "watch" a movie from a list given by the "movies.csv" file.

## How it works:

* :arrow_forward: **Start Menu:**
    * :arrow_right: **Login:** query **users.csv** file to find an user that login matches with given "login" string. If a **users.csv** file doesn't exist, it will read the given **usuarios.csv** and create the new **users.csv** file (the difference between both, is the fact that **users.csv** will only be created once, and will add a "deleted" column at the end of each row) and try to read again. If the user is not found after the new **users.csv** has been created, it will return -1, as a response to say that user is not registered. Otherwise, if an user is found, it will return the *user_id*. 
    **Note:** it will check if user is deleted or not. If it finds an user with the same login but it's deleted (the last column is 1 instead of 0), it will throw an error saying that user doesn't exist.
    
    * :arrow_heading_down: **Register:** asks to user for a login, query the **users.csv** file to find if that given name matches with a existent user and it's not deleted. In this case, it will return an error. Otherwise, it will ask for a password and if it fits in the pattern (alphanumeric), the program will ask to repeat the password, compare both and validate the user register.

    * :door: **Quit**: read **users.csv** and **watched.csv**, empty the **usuarios.csv** and write over it with new users data in this order, skipping deleted users:
    login,password,watched1,avaliation1,watchDate1,watched2...
 
    
* :abcd: **Main Menu:**
    * :page_facing_up: **List Movies:** initialize a page as 0, and lists from `(page * 10) + 1` to `(page + 1) * 10`, by querying **filmes-grande.csv** file and returning each line data as an *Movie* struct corresponding to the page (in this case will return from line 1 to line 10) and saves each *Movie* data in an *Movie* array because it's faster to load movie data when user select one of the 10 listed if it's in the buffer and it don't costs much memory because it's only 10 by 10.
    User can watch one of listed movies or back to the list.
         * Watching: ask for a avaliation from 0 to 10 (float) and for the date that user watched, returning to Main Menu at the end.
         Creates a new line at **watched.csv** like:
         *user_id,movie_id,avaliation,day/month/year*
         if file doesn't exists yet, it will create a new one.
         * Returning: return user to list where he was previously.
    
    * :bust_in_silhouette: **My Profile:** open "User Menu" (description below).

    * :mag_right: **Find Movie:** wait user input a string to be matched with movies names. Returns a list with all movies that matches with the given string.

    * :arrow_left: **Exit:** quit from the application, passing in the last menu "Quit" making it functionality and quiting the application.

* :abc: **User Menu:**
    * :clock1: **User History:** asks for "D" or "N" to list user history by Date or Avaliation, listing all watched movies. It queries all the **watched.csv** looking for all rows that contain *user_id* equals to the actual user's ID.

    * :negative_squared_cross_mark: **Delete Account:** query **users.csv** file looking for the actual user's row and replaces the last 0 to 1, in order to mark the user as "deleted".

    * :arrow_left: **Back:** back user to Main Menu.