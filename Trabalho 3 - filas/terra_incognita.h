#ifndef TERRA_INCOGNITA_H
#define TERRA_INCOGNITA_H

#define MAX_EXPLORADORES 1000

#define TERRA_INCOGNITA 0
#define TERRA_PLANICIE 1
#define TERRA_FLORESTA 2
#define TERRA_MONTANHA 3
#define TERRA_AGUA 4

typedef int cellulae_func(int, int);

void intro(int argc, char *argv[], int *nExplorator, int positio[][2]);

char explorator(int *id, int *typus);

void tabula(cellulae_func *cell, int lat, int alt);

void veritas(cellulae_func *cell, int lat, int alt);

void relinquo();

#endif