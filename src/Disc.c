#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Aluno.h"
#include "../include/Disc.h"

Disc *newDisc(int numero, char *nome, char *prof, int creditos, Disc *prev) {
    Disc *new = (Disc *) malloc(sizeof(Disc));
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

    new->alunoList = NULL;
    
    return new;
}

void removeDiscbyIndex(Disc **endHead, int index) {
    Disc *iter = (*endHead);
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

void showDiscs(Disc **endHead) {
    Disc *iter = (*endHead);
    if(iter) {
        printf("%5s %6s %50s %50s %8s\n","INDEX","NUMERO", "NOME", "PROF", "CREDITOS");
        int tam = iter->index + 1;
        while(iter->prev) iter = iter->prev;
        for(int i=0;i<tam;i++) {
            printf("%5d %6d %50s %50s %8d\n",iter->index,iter->numero,iter->nome, iter->prof,iter->creditos);
            iter = iter->next;
        }
    } else {
        // NADA PRA MOSTRAR
        // printf("NADA\n");
    }
    iter = NULL;
    free(iter);
}

Disc *loadDiscsFromText(char *filename) {
    FILE *fptr = fopen(filename,"r");
    if(!fptr) return NULL;
    int tam;
    fscanf(fptr,"%d\n",&tam);
    if(tam) {
        Disc *newAlunos = NULL;
        int numero;
        char nome[100];
        char prof[100];
        int creditos;
        for(int i=0;i<tam;i++) {
            fscanf(fptr,"%d\n%[^\n]\n%[^\n]\n%d",&numero,nome,prof,&creditos);
            newAlunos = newDisc(numero,nome,prof,creditos,newAlunos);
        }
        return newAlunos;
    }
    return NULL;
}

void saveDiscInFile(Disc **endHead, char *filename) {
    FILE *fptr = fopen(filename,"w");
    if(fptr) {
        Disc *iter = (*endHead);
        if(iter) {
            int tam = iter->index + 1;
            fprintf(fptr,"%d\n",tam);
            while(iter->prev) iter = iter->prev;
            for(int i=0;i<tam;i++) {
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
        exit(1);
    }
}

void removeDiscbyDiscName(Disc **endHead, char *nome) {
    if(*endHead) {
        Disc *iter = (*endHead);
        while(strcmp(iter->nome,nome)!=0) {
            if(iter->prev) iter = iter->prev;
            else {
                iter = NULL;
                free(iter);
                return ;
            }
        }
        removeDiscbyIndex(endHead,iter->index);
        iter = NULL;
        free(iter);
    } else {
        return ;
    }
}