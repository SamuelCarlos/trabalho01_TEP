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

Movie getMovieByID(int id);

void findAndListMovies();

void listTenMovies(int page);

#endif //movie_h