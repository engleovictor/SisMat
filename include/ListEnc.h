#ifndef LISTENC_H
#define LISTENC_H

#include "./Aluno.h"
#include "./Disc.h"

typedef struct listencaluno {
    int numero;
    char nome[100];
    char cpf[12];
    struct listencaluno *next;
    struct listencaluno *prev;
    int index; 
    Disc *discList;
    
} LEA;

typedef struct listencdisc {
    int numero;
    char nome[100];
    char prof[100];
    int creditos;
    struct listencdisc *next;
    struct listencdisc *prev;
    int index;
    Aluno *alunoList;
} LED;

LEA *newLEA(int numero, char *nome, char *cpf, LEA *prev);
void removeLEAbyIndex(LEA **endHead, int index);
void showLEAs(LEA **endHead);
LEA *loadLEAsFromText(char *filename);
void saveLEAInFile(LEA **endHead, char *filename);
void attachDiscListFromFile(LEA **endHead, char *filename);


LED *newLED(int numero, char *nome, char *prof, int creditos,LED *prev);
void removeLEDbyIndex(LED **endHead, int index);
void showLEDs(LED **endHead);
LED *loadLEDsFromText(char *filename);
void saveLEDInFile(LED **endHead, char *filename);
void attachAlunoListFromFile(LED **endHead, char *filename);

#endif /* LISTENC_H */