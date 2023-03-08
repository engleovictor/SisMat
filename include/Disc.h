#ifndef DISC_H
#define DISC_H

#include "./Aluno.h"

typedef struct disc {
    int numero;
    char nome[100];
    char prof[100];
    int creditos;
    struct disc *next;
    struct disc *prev;
    Aluno *alunoList;
    int index;
} Disc;

Disc *newDisc(int numero, char *nome, char *prof, int creditos, Disc *prev);
void removeDiscbyIndex(Disc **endHead, int index);
void showDiscs(Disc **endHead);
Disc *loadDiscsFromText(char *filename);
void saveDiscInFile(Disc **endHead, char *filename);
void removeDiscbyDiscName(Disc **endHead, char *nome);

#endif /* DISC_H */