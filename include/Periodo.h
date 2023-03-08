#ifndef PERIODO_H
#define PERIODO_H

#include "./Disc.h"

typedef struct periodo {
    char data[7];
    Disc *discList;
    int index;
    struct periodo *next;
    struct periodo *prev;
} Periodo;

Periodo *newPeriodo(char *data, Periodo *prev);
void removePeriodobyIndex(Periodo **endHead, int index);
void showPeriodos(Periodo **endHead);
Periodo *loadData(char *filename);
void saveData(Periodo **periodo, char *filename);

#endif /* PERIODO_H */