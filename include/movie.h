#ifndef MOVIE_H
#define MOVIE_H

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
@param int id: movie id to query the specific one;
@return Movie struct who contains movie data;
*/
Movie getMovieByID(int id);

/*
@brief this function is made just for organization, it will
ask for a movie name and query movies file searching for a
movie who name matches the given string;
*/
void findAndListMovies();

/*
@brief query movies file and list ten movies starting from given 
page to keep console screen clean;
@param int page: page >= 1, it's the param who tells what ten movies
are about to be printed;
*/
void listTenMovies(int page);

#endif //movie_h