#ifndef WATCHED_H
#define WATCHED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;           // user id (from 1 to infinite)
    int user_id;
    int movie_id;
    float user_avaliation;
    int day;
    int month;
    int year;
} Watched;

/*
@brief query and lists all movies watched by the user with watched
date and user avaliation;
@param int user_id: user id to query the watched file;
@param char filter: expected: (D: filter by date, N: 
filter by avaliation);
@return array of Watched with all Watched movies by the user;
*/
void showHistory(const int user_id);

/*
@brief filter the search result by date;
@param Watched *all_watched: list of all watched movies;
@return filtered by date array of Watched;
*/
void sortWatchedByDate(Watched *watched, int manyWatched);

/*
@brief filter the search result by user avaliations;
@param Watched *all_watched: list of all watched movies;
@return filtered by avaliation array of Watched;
*/
void sortWatchedByAvaliation(Watched *watched, int manyWatched);

/*
@brief a interface who ask user avaliation and date he watched the movie,
and then call writeNewWatched;
@param int user_id: user info to add on file;
@param int movie_id: movie info to add on file;
*/
void watchMovie(const int verbosity, const int user_id, const int movie_id);

/*
@brief write a new watched movie on watched file;
@param Watched watched: Watched struct with all data needed to print a new
record on watched file;
*/
void writeNewWatched(Watched watched);

/*
@brief query watched file and search for all user's records;
@param const int user_id: user identification;
@param int *manyWatched: pointer who tells to function that calls this
how many movies are about to be returned;
*/
Watched *getUserHistory(const int user_id, int *manyWatched);

#endif //watched_h