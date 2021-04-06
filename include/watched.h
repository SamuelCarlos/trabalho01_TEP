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
void showHistory(int user_id);

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
@brief write a new watched movie on watched file;
@param int user_id: user info to add on file;
@param int movie_id: movie info to add on file;
*/
void watchMovie(const int verbosity, int user_id, int movie_id);

void writeNewWatched(Watched watched);

Watched *getUserHistory(int user_id, int *manyWatched);










#endif //watched_h