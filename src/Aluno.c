#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Aluno.h"

Aluno *newAluno(int numero, char *nome, char *cpf, Aluno *prev) {
    Aluno *new = (Aluno *) malloc(sizeof(Aluno));
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
    return new;
}

void removeAlunobyIndex(Aluno **endHead, int index) {
    Aluno *iter = (*endHead);
    if((*endHead)->index == index && index != 0) {
        (*endHead) = (*endHead)->prev;
        (*endHead)->next = NULL;
        free(iter);
        return ;
    }
    while(iter->index != index) iter = iter->prev; 
    if(!(iter->prev)&!(iter->next)) {
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

void removeAlunobyCPF(Aluno **endHead, char *cpf) {
    if(*endHead) {
        Aluno *iter = (*endHead);
        while(strcmp(iter->cpf,cpf)!=0) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        }
        removeAlunobyIndex(endHead,iter->index);
        iter = NULL;
        free(iter);
    } else {
        return ;
    }
}

void showAlunos(Aluno **endHead) {
    Aluno *iter = (*endHead);
    if(iter) {
        printf("%5s %6s %50s %11s\n","INDEX","NUMERO", "NOME", "CPF");
        int tam = iter->index + 1;
        while(iter->prev) iter = iter->prev;
        for(int i=0;i<tam;i++) {
            printf("%5d %6d %50s %11s\n",iter->index,iter->numero,iter->nome, iter->cpf);
            iter = iter->next;
        }
    } else {
        // NADA PRA MOSTRAR
    }
    iter = NULL;
    free(iter);
}

Aluno *loadAlunosFromText(char *filename) {
    FILE *fptr = fopen(filename,"r");
    if(!fptr) return NULL;
    int tam;
    fscanf(fptr,"%d\n",&tam);
    if(tam) {
        Aluno *newDiscs = NULL;
        int numero;
        char nome[100];
        char cpf[12];
        for(int i=0;i<tam;i++) {
            fscanf(fptr,"%d\n%[^\n]\n%[^\n]",&numero,nome,cpf);
            newDiscs = newAluno(numero,nome,cpf,newDiscs);
        }
        return newDiscs;
    }
    return NULL;
}

void saveAlunoInFile(Aluno **endHead, char *filename) {
    FILE *fptr = fopen(filename,"w");
    if(fptr) {
        Aluno *iter = (*endHead);
        if(iter) {
            int tam = iter->index + 1;
            fprintf(fptr,"%d\n",tam);
            while(iter->prev) iter = iter->prev;
            for(int i=0;i<tam;i++) {
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
        exit(1);
    }
}