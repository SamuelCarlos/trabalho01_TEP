#include "watched.h"

void writeNewWatched(Watched watched) {
    FILE * watches;

    watches = fopen("./data/watched.csv","a+");

    fprintf(watches, "%d,%d,%.2f,%d/%d/%d\n", watched.user_id, watched.movie_id, watched.user_avaliation, watched.day, watched.month, watched.year);

    fclose(watches);
}