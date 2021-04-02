#ifndef WATCHED_H
#define WATCHED_H

typedef struct {
    int id;           // user id (from 1 to infinite)
    int user_id;
    int movie_id;
    float user_avaliation;
    char *created_at;
} Watched;

/*
@brief query and lists all movies watched by the user with watched
date and user avaliation;
@param int user_id: user id to query the watched file;
@param char filter: expected: (D: filter by date, N: 
filter by avaliation);
@return array of Watched with all Watched movies by the user;
*/
Watched *listAllWatched(int user_id, char filter);

/*
@brief filter the search result by date;
@param Watched *all_watched: list of all watched movies;
@return filtered by date array of Watched;
*/
Watched *filterByDate(Watched *all_watched);

/*
@brief filter the search result by user avaliations;
@param Watched *all_watched: list of all watched movies;
@return filtered by avaliation array of Watched;
*/
Watched *filterByAvaliation(Watched *all_watched);

/*
@brief write a new watched movie on watched file;
@param int user_id: user info to add on file;
@param int movie_id: movie info to add on file;
*/
void writeNewWatched(int user_id, int movie_id);

#endif //watched_h