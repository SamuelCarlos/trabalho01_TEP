#ifndef WATCHED_H
#define WATCHED_H

typedef struct {
    int id;           // user id (from 1 to infinite)
    int user_id;
    int movie_id;
    float user_avaliation;
    char *created_at;
    char *updated_at;
} Watched;


#endif //watched_h