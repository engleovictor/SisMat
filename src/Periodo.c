#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/Periodo.h"

Periodo *newPeriodo(char *data, Periodo *prev) {
    Periodo *new = (Periodo *) malloc(sizeof(Periodo));
    strcpy(new->data,data);
    new->prev = prev;
    new->next = NULL;
    if(!prev) new->index = 0;
    else {
        new->index = prev->index + 1;
        prev->next = new;    
    }

    new->discList = NULL;

    return new;
}

void removePeriodobyIndex(Periodo **endHead, int index) {
    Periodo *iter = (*endHead);
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

void showPeriodos(Periodo **endHead) {
    Periodo *iter = (*endHead);
    if(iter) {
        printf("%5s %7s\n","INDEX","PERIODO");
        int tam = iter->index + 1;
        while(iter->prev) iter = iter->prev;
        for(int i=0;i<tam;i++) {
            printf("%5d %7s\n",iter->index,iter->data);
            iter = iter->next;
        }
    } else {
        // NADA PRA MOSTRAR
    }
    iter = NULL;
    free(iter);
}

Periodo *loadData(char *filename) {
    FILE *fptr = fopen(filename,"r");
    if(fptr) {
        Periodo *new = NULL;
        int tam0, tam1, tam2;
        char data[7];

        int numeroDisc, creditos;
        char nomeDisc[50], prof[50];

        int numeroAluno;
        char nomeAluno[50], cpf[12];

        fscanf(fptr,"%d\n",&tam0);
        for(int i=0;i<tam0;i++) {
            fscanf(fptr,"%[^\n]",data);
            fscanf(fptr,"%d\n",&tam1);
            Disc *discs = NULL;
            for(int j=0;j<tam1;j++) {
                fscanf(fptr,"%d\n%[^\n]\n%[^\n]\n%d\n",&numeroDisc,nomeDisc,prof,&creditos);
                fscanf(fptr,"%d\n",&tam2);
                Aluno *alunos = NULL;
                for(int k=0;k<tam2;k++) {
                    fscanf(fptr,"%d\n%[^\n]\n%[^\n]\n",&numeroAluno,nomeAluno,cpf);
                    alunos = newAluno(numeroAluno,nomeAluno,cpf,alunos);
                }
                discs = newDisc(numeroDisc,nomeDisc,prof,creditos,discs);
                discs->alunoList = alunos;
            }
            new = newPeriodo(data,new);
            new->discList = discs;
        }

        return new;
    } else {
        return NULL;
    }
    
}

void saveData(Periodo **periodo, char *filename) {
    FILE *fptr = fopen(filename,"w");
    if(fptr) {
        if(*periodo) {
            Periodo *iter = *periodo;
            int tam0 = iter->index + 1;
            fprintf(fptr,"%d\n",tam0);
            while(iter->prev) iter = iter->prev;
            for(int i=0;i<tam0;i++) {
                fprintf(fptr,"%s\n",iter->data);
                if(iter->discList) {
                    int tam1 = iter->discList->index + 1;
                    fprintf(fptr,"%d\n",tam1);
                    while(iter->discList->prev) iter->discList = iter->discList->prev;
                    for(int j=0;j<tam1;j++) {
                        fprintf(fptr,"%d\n%s\n%s\n%d\n",iter->discList->numero,iter->discList->nome,iter->discList->prof,iter->discList->creditos);
                        if(iter->discList->alunoList) {
                            int tam2 = iter->discList->alunoList->index + 1;
                            fprintf(fptr,"%d\n",tam2);
                            while(iter->discList->alunoList->prev) iter->discList->alunoList = iter->discList->alunoList->prev;
                            for(int k=0;k<tam2;k++) {
                                fprintf(fptr,"%d\n%s\n%s\n",iter->discList->alunoList->numero,iter->discList->alunoList->nome,iter->discList->alunoList->cpf);
                                iter->discList->alunoList = iter->discList->alunoList->next;
                            }
                        } else {
                            fprintf(fptr,"0\n");
                        }
                        iter->discList = iter->discList->next; 
                    }
                } else {
                    fprintf(fptr,"0\n");
                }
                iter = iter->next;
            }
        } else {
            fprintf(fptr,"0\n");
        }
    } else {
        printf("ERRO AO SALVAR\n");
        exit(1);
    }
}
