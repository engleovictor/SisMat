#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Aluno.h"
#include "../include/Disc.h"
#include "../include/ListEnc.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"

LEA *newLEA(int numero, char *nome, char *cpf, LEA *prev) {
    LEA *new = (LEA *) malloc(sizeof(LEA));
    new->numero = numero;
    strcpy(new->nome,nome);
    strcpy(new->cpf,cpf);
    new->prev = prev;
    new->next = NULL;
    if(!prev) new->index = 0;
    else {
        new->index = prev->index + 1;
        prev->next = new;    
    }
    //ADD DISCLIST;
    char filename[24] = "LEAfiles/LEA";
    strcat(filename,cpf);
    attachDiscListFromFile(&new,filename);
    return new;
}

void removeLEAbyIndex(LEA **endHead, int index) {
    LEA *iter = (*endHead);
    if((*endHead)->index == index && index != 0) {
        (*endHead) = (*endHead)->prev;
        (*endHead)->next = NULL;
        free(iter);
        return ;
    }
    while(iter->index != index) iter = iter->prev; 
    if((!(iter->prev))&&(!(iter->next))) {
        (*endHead) = NULL;
        free(iter);
        return ;
    }
    if(iter->prev) iter->prev->next = iter->next;
    if(iter->next) iter->next->prev = iter->prev;
    while(iter->next) {
        iter = iter->next;
        iter->index--;
    }
    iter = NULL;
    free(iter);
}

void showLEAs(LEA **endHead) {
    LEA *iter = (*endHead);
    if(iter) {
        printf("%5s %6s %38s %11s\n",COLOR_YELLOW "INDEX","NUMERO", "NOME", "CPF" COLOR_RESET);
        int tam = iter->index + 1;
        while(iter->prev) iter = iter->prev;
        for(int i=0;i<tam;i++) {
            printf("%5d %6d %38s %11s\n",iter->index,iter->numero,iter->nome, iter->cpf);
            iter = iter->next;
        }
    } else {
        // NADA PRA MOSTRAR
    }
    iter = NULL;
    free(iter);
}

LEA *loadLEAsFromText(char *filename) {
    FILE *fptr = fopen(filename,"r");
    if(!fptr) return NULL;
    int tam;
    fscanf(fptr,"%d\n",&tam);
    if(tam) {
        LEA *newDiscs = NULL;
        int numero;
        char nome[100];
        char cpf[12];
        for(int i=0;i<tam;i++) {
            fscanf(fptr,"%d\n%[^\n]\n%[^\n]",&numero,nome,cpf);
            newDiscs = newLEA(numero,nome,cpf,newDiscs);
        }
        return newDiscs;
    }
    return NULL;
}

void saveLEAInFile(LEA **endHead, char *filename) {
    FILE *fptr = fopen(filename,"w");
    if(fptr) {
        LEA *iter = (*endHead);
        if(iter) {

            int tam = iter->index + 1;
            fprintf(fptr,"%d\n",tam);
            while(iter->prev) iter = iter->prev;
            for(int i=0;i<tam;i++) {
                char listfilename[24] = "LEAfiles/LEA";
                strcat(listfilename,iter->cpf);
                saveDiscInFile(&(iter->discList),listfilename);
                fprintf(fptr,"%d\n%s\n%s\n",iter->numero,iter->nome,iter->cpf);
                iter = iter->next;
            }
            iter = NULL;
            free(iter);
        } else {
            fprintf(fptr,"0\n");
        }
    } else {
        printf("ERRO AO SALVAR!! SAINDO...\n");
        printf("Por favor use config.ps1 ou config.sh\n");
        remove("LEA.txt");
        exit(1);
    }
}

void attachDiscListFromFile(LEA **endHead, char *filename) {
    (*endHead)->discList = loadDiscsFromText(filename);
}

LED *newLED(int numero, char *nome, char *prof, int creditos,LED *prev) {
    LED *new = (LED *) malloc(sizeof(LED));
    new->numero = numero;
    new->creditos = creditos;
    strcpy(new->nome,nome);
    strcpy(new->prof,prof);
    new->prev = prev;
    new->next = NULL;
    if(!prev) new->index = 0;
    else {
        new->index = prev->index + 1;
        prev->next = new;    
    }
    //ADD ALUNOLIST;
    char filename[104] = "LEDfiles/LED";
    strcat(filename,nome);
    attachAlunoListFromFile(&new,filename);
    return new;
}

void removeLEDbyIndex(LED **endHead, int index) {
    LED *iter = (*endHead);
    if((*endHead)->index == index && index != 0) {
        (*endHead) = (*endHead)->prev;
        (*endHead)->next = NULL;
        free(iter);
        return ;
    }
    while(iter->index != index) iter = iter->prev; 
    if((!(iter->prev))&&(!(iter->next))) {
        (*endHead) = NULL;
        free(iter);
        return ;
    }
    if(iter->prev) iter->prev->next = iter->next;
    if(iter->next) iter->next->prev = iter->prev;
    while(iter->next) {
        iter = iter->next;
        iter->index--;
    }
    iter = NULL;
    free(iter);
}

void showLEDs(LED **endHead) {
    LED *iter = (*endHead);
    if(iter) {
        printf("%5s %6s %38s %50s %8s\n",COLOR_YELLOW "INDEX","NUMERO", "NOME", "PROF", "CREDITOS" COLOR_RESET);
        int tam = iter->index + 1;
        while(iter->prev) iter = iter->prev;
        for(int i=0;i<tam;i++) {
            printf("%5d %6d %38s %50s %8d\n",iter->index,iter->numero,iter->nome, iter->prof,iter->creditos);
            iter = iter->next;
        }
    } else {
        // NADA PRA MOSTRAR
        // printf("NADA\n");
    }
    iter = NULL;
    free(iter);
}

LED *loadLEDsFromText(char *filename) {
    FILE *fptr = fopen(filename,"r");
    if(!fptr) return NULL;
    int tam;
    fscanf(fptr,"%d\n",&tam);
    if(tam) {
        LED *newAlunos = NULL;
        int numero;
        char nome[100];
        char prof[100];
        int creditos;
        for(int i=0;i<tam;i++) {
            fscanf(fptr,"%d\n%[^\n]\n%[^\n]\n%d",&numero,nome,prof,&creditos);
            newAlunos = newLED(numero,nome,prof,creditos,newAlunos);
        }
        return newAlunos;
    }
    return NULL;
}

void saveLEDInFile(LED **endHead, char *filename) {
    FILE *fptr = fopen(filename,"w");
    if(fptr) {
        LED *iter = (*endHead);
        if(iter) {

            int tam = iter->index + 1;
            fprintf(fptr,"%d\n",tam);
            while(iter->prev) iter = iter->prev;
            for(int i=0;i<tam;i++) {
                char listfilename[104] = "LEDfiles/LED";
                strcat(listfilename,iter->nome);
                saveAlunoInFile(&(iter->alunoList),listfilename);
                fprintf(fptr,"%d\n%s\n%s\n%d\n",iter->numero,iter->nome,iter->prof,iter->creditos);
                iter = iter->next;
            }
            iter = NULL;
            free(iter);
        } else {
            fprintf(fptr,"0\n");
        }
    } else {
        printf("ERRO AO SALVAR!! SAINDO...\n");
        printf("Por favor use config.ps1 ou config.sh\n");
        remove("LED.txt");
        exit(1);
    }
}

void attachAlunoListFromFile(LED **endHead, char *filename) {
    (*endHead)->alunoList = loadAlunosFromText(filename);
}
