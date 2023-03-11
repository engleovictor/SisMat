#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/SisMat.h"

int cadastrarAluno(Aluno **endHead) {
    int numero;
    char nome[100], cpf[12];
    printf("Digite seu Numero: ");
    scanf("%d", &numero);
    getchar();
    printf("Digite seu Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite seu CPF: ");
    scanf("%s", cpf);

    Aluno *iter = *endHead;
    
    if(iter) {
        
        int tam = iter->index + 1; 
         
        for(int i=0;i<tam;i++) {  
            if(strcmp(iter->cpf,cpf) == 0) {
                iter = NULL;
                free(iter);
                return 1;
            }
            iter = iter->prev;
        }
    }

    iter = NULL;
    free(iter);

    *endHead = newAluno(numero,nome,cpf,*endHead);

    return 0;
}

int cadastrarMateria(Disc **endHead) {
    int numero, creditos;
    char nome[100], prof[100];
    printf("Digite seu Numero: ");
    scanf("%d", &numero);
    getchar();
    printf("Digite seu Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite seu Professor: ");
    getchar();
    scanf("%[^\n]", prof);
    printf("Digite os Creditos: ");
    scanf("%d", &creditos);

    Disc *iter = *endHead;

    if(iter) {
        int tam = iter->index + 1;
        
        for(int i=0;i<tam;i++) {
            if(strcmp(iter->prof,prof) == 0) {
                iter = NULL;
                free(iter);
                return 1;
            }
            iter = iter->prev;
        }
    }

    iter = NULL;
    free(iter);

    *endHead = newDisc(numero,nome,prof,creditos,*endHead);

    return 0;
}

int cadastrarPeriodo(Periodo **endHead) {
    char data[7];
    getchar();
    printf("Digite Periodo: ");
    scanf("%[^\n]", data);

    Periodo *iter = *endHead;

    if(iter) {
        int tam = iter->index + 1;
        
        for(int i=0;i<tam;i++) {
            if(strcmp(iter->data,data) == 0) {
                iter = NULL;
                free(iter);
                return 1;
            }
            iter = iter->prev;
        }
    }

    iter = NULL;
    free(iter);

    *endHead = newPeriodo(data,*endHead);

    return 0;
}

int cadastrarMateriaemPeriodo(Disc **discHead, Periodo **periodoHead) {
    if(!((*periodoHead)&&(*discHead))) return 1;
    int opt;
    Periodo *iterPeriodo = *periodoHead;
    showDiscs(discHead);
    printf("Escolha o Materia que deseja cadastrar no Periodo: ");
    scanf("%d",&opt);
    Disc *iterDisc = *discHead;
    while(iterDisc->index != opt) iterDisc = iterDisc->prev;
    iterPeriodo->discList = newDisc(iterDisc->numero,iterDisc->nome,iterDisc->prof,iterDisc->creditos,iterPeriodo->discList);
    iterDisc = NULL;
    free(iterDisc);
    iterPeriodo = NULL;
    free(iterPeriodo);
    return 0;
}

int cadastrarAlunoemMateria(Aluno **alunoHead, Periodo **periodo) {
    if(!((*periodo)&&(*alunoHead))) return 1;
    showAlunos(alunoHead);
    printf("Escolha o aluno que deseja cadastrar: ");
    int opt;
    scanf("%d",&opt);
    Aluno *iterAluno = *alunoHead;
    while(iterAluno->index != opt) iterAluno = iterAluno->prev;
    showDiscs(&(*periodo)->discList);
    printf("Escolha a materia que deseja matricula-lo: ");
    scanf("%d",&opt);
    Disc *iterDisc = (*periodo)->discList;
    while(iterDisc->index != opt) iterDisc = iterDisc->prev;
    iterDisc->alunoList = newAluno(iterAluno->numero,iterAluno->nome,iterAluno->cpf,iterDisc->alunoList);
    iterDisc = NULL;
    free(iterDisc);
    iterAluno = NULL;
    free(iterAluno);
    return 0;
}

int removerAlunoDeMateria(Periodo **periodo) {
    Disc *iterDisc = (*periodo)->discList;
    if(!iterDisc) return 1;
    showDiscs(&iterDisc);
    printf("Escolha a Materia da Qual deseja remover aluno: ");
    int opt;
    scanf("%d", &opt);
    while(iterDisc->index != opt) iterDisc = iterDisc->prev;
    if(!(iterDisc->alunoList)) return 1;
    showAlunos(&(iterDisc->alunoList));
    printf("Escolha qual aluno remover: ");
    scanf("%d",&opt);
    removeAlunobyIndex(&(iterDisc->alunoList),opt);
    iterDisc = NULL;
    free(iterDisc);
    return 0;
}

int removerMateriadePeriodo(Periodo **periodo) {
    if(!((*periodo)->discList)) return 1;
    showDiscs(&((*periodo)->discList));
    printf("Escolha a Materia para remover: ");
    int opt;
    scanf("%d",&opt);
    removeDiscbyIndex(&((*periodo)->discList),opt);
    return 0;
}

int removerPeriodo(Periodo **periodos) {
    showPeriodos(periodos);
    printf("Escolha qual periodo deseja Remover: ");
    int opt;
    scanf("%d", &opt);
    removePeriodobyIndex(periodos,opt);
    return 0;
}

int removerMateria(Disc **discHead, Periodo **periodoHead) {
    if(!(*discHead)) return 1;
    showDiscs(discHead);
    printf("Escolha a materia que deseja remover: ");
    int opt;
    scanf("%d", &opt);
    if(*periodoHead) {
        Disc *iterDisc = *discHead;
        while(iterDisc->index != opt) iterDisc = iterDisc->prev;
        Periodo *iterPeriodo = *periodoHead;
        while(iterPeriodo->prev) {
            removeDiscbyDiscName(&(iterPeriodo->discList),iterDisc->nome);
            iterPeriodo = iterPeriodo->prev;
        }
        removeDiscbyDiscName(&(iterPeriodo->discList),iterDisc->nome);
    }
    removeDiscbyIndex(discHead,opt);
    return 0;
}

int removerAluno(Aluno **alunoHead, Periodo **periodoHead) {
    if(!(*alunoHead)) return 1;
    showAlunos(alunoHead);
    printf("Escolha o Aluno que deseja remover: ");
    int opt;
    scanf("%d", &opt);
    Aluno *iterAluno = *alunoHead;
    while(iterAluno->index != opt) iterAluno = iterAluno->prev;
    if (*periodoHead) {
        while((*periodoHead)->prev) {
            
            while((*periodoHead)->discList->prev) {
                removeAlunobyCPF(&((*periodoHead)->discList->alunoList),iterAluno->cpf);
                (*periodoHead)->discList = (*periodoHead)->discList->prev;
            }
            removeAlunobyCPF(&((*periodoHead)->discList->alunoList),iterAluno->cpf);
        }

        while((*periodoHead)->discList->prev) {
            removeAlunobyCPF(&((*periodoHead)->discList->alunoList),iterAluno->cpf);
            (*periodoHead)->discList = (*periodoHead)->discList->prev;
        }
        removeAlunobyCPF(&((*periodoHead)->discList->alunoList),iterAluno->cpf);
        while((*periodoHead)->next) (*periodoHead) = (*periodoHead)->next;
    }
    removeAlunobyIndex(alunoHead,opt);
    return 0;
}
