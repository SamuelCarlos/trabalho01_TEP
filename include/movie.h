#ifndef MOVIE_H
#define MOVIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;           // user id (from 1 to infinite)
    char *title;
    int year;
    int duration;
    float avaliation;
    char *description;
} Movie;

/*
@brief query movies file searching for a specific given movie;
@param const int id: movie id to query the specific one;
@return Movie struct who contains movie data;
*/
Movie getMovieByID(const int id);

/*
@brief query movies file searching for movies that title matches
with given string;
@param char *string: string to find for;
@param int *movieCount: pointer who tells where function is called
how many movies will be returned;
@return Movie struct array who contains movies data;
*/
Movie *getMovieMatches(char *string, int *movieCount);

/*
@brief show movie data and ask if user will watch or back;
@param const int verbosity: defines menus are going to be printed;
@param Movie movie: movie to be printer;
@param const int user_id;
@return 1: movie watched;
        0: not watched;
*/
int showMovie(const int verbosity, Movie movie, const int user_id);

/*
@brief this function is made just for organization, it will
ask for a movie name and query movies file searching for a
movie who name matches the given string;
*/
void findAndListMovies();

/*
@brief query movies file and list ten movies starting from given 
page to keep console screen clean;
*/
void listTenMovies(const int verbosity, const int user_id);

/*
@brief print all movie metadata;
*/
void printMovieMetadata(Movie movie);

/*
@brief interface to ask user for the string he wants to search;
@param const int verbosity: defines menus are going to be printed;
@param const int user_id: user identificator;
*/
void searchMovie(const int verbosity, const int user_id);

#endif //movie_h