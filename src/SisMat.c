#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/SisMat.h"

void cadastrarAluno(LEA **endHead) {
    int numero;
    char nome[100], cpf[12];
    printf("Digite seu Numero: ");
    scanf("%d", &numero);
    getchar();
    printf("Digite seu Nome: ");
    scanf(" %[^\n]", nome);
    printf("Digite seu CPF: ");
    scanf("%s", cpf);

    LEA *iter = *endHead;
    int tam = iter->index + 1;
    if(strcmp(iter->cpf,cpf) == 0) return ;
    for(int i=0;i<tam;i++) {
        iter = iter->prev;
        if(strcmp(iter->cpf,cpf) == 0) return ;
    }

    iter = NULL;
    free(iter);

    *endHead = newLEA(numero,nome,cpf,*endHead);

    return ;
}

void cadastrarMateria(LED **endHead) {
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

    LED *iter = *endHead;
    int tam = iter->index + 1;
    if(strcmp(iter->prof,prof) == 0) return ;
    for(int i=0;i<tam;i++) {
        iter = iter->prev;
        if(strcmp(iter->prof,prof) == 0) return ;
    }

    iter = NULL;
    free(iter);

    *endHead = newLED(numero,nome,prof,creditos,*endHead);

    return ;
}

void cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead) {
    int opt;
    showLEAs(alunoHead);
    LEA *iter0 = *alunoHead;
    printf("Escolha o Aluno por index: ");
    scanf("%d",&opt);
    //
    int max_index = iter0->index;
    if(opt > max_index) return ;
    //
    while(iter0->index != opt) iter0 = iter0->prev;

    showLEDs(discHead);
    LED *iter1 = *discHead;
    printf("Escolha a Materia por index: ");
    scanf("%d",&opt);
    //
    max_index = iter1->index;
    if(opt > max_index) return ;
    //
    while(iter1->index != opt) iter1 = iter1->prev;

    //////////////////////////////////////////////////// VERIFICAR SE O ALUNO JA ESTA NA MATERIA !!

    iter1->alunoList = newAluno(iter0->numero,iter0->nome,iter0->cpf,iter1->alunoList);
    iter0->discList  = newDisc(iter1->numero,iter1->nome,iter1->prof,iter1->creditos,iter0->discList);
    iter0 = NULL;
    iter1 = NULL;
    free(iter0);
    free(iter1);

    return ;
}

void removerAlunoDeMateria(LED **discHead, LEA **alunoHead) {
    showLEDs(discHead);
    printf("Escolha o Index da Materia da qual gostaria de remover o Aluno: ");
    int opt;
    scanf("%d",&opt);
    LED *iter = *discHead;
    //
    int max_index = iter->index;
    if(opt > max_index) return ;
    //
    while(iter->index != opt) iter = iter->prev;
    showAlunos(&(iter->alunoList));
    printf("Escolha o Index do Aluno que deseja remover dessa materia: ");
    scanf("%d",&opt);
    
    Aluno *aluno = iter->alunoList;
    //
    max_index = aluno->index;
    if(opt > max_index) return ;
    //
    while(aluno->index != opt) aluno = aluno->prev;
    LEA *iterAluno = *alunoHead;
    while(strcmp(iterAluno->cpf,aluno->cpf)!=0) iterAluno = iterAluno->prev;

    removeDiscbyDiscName(&(iterAluno->discList),iter->nome);

    removeAlunobyIndex(&(iter->alunoList),opt);
    
    aluno = NULL;
    free(aluno);
    iterAluno = NULL;
    free(iterAluno);
    iter = NULL;
    free(iter);

    return ;
}

void removerAluno(LEA **alunoHead, LED **discHead) {
    showLEAs(alunoHead);
    printf("Escolha o Aluno que deseja remover por Index: ");
    int opt;
    LEA *iter = *alunoHead;
    scanf("%d",&opt);
    //
    int max_index = iter->index;
    if(opt > max_index) return ;
    // 
    while(iter->index != opt) iter = iter->prev;
    int removeableIndex = iter->index;
    //
    char filename[24] = "LEAfiles/LEA";
    strcat(filename,iter->cpf);
    int rmst = remove(filename);
    // 
    LED *iterDisc = *discHead;
    if(iterDisc) {
        int tam = iterDisc->index + 1;
        for(int i=0;i<tam;i++) {
            removeAlunobyCPF(&(iterDisc->alunoList),iter->cpf);
            iterDisc = iterDisc->prev;
        }
    }
    removeLEAbyIndex(alunoHead, removeableIndex);
    iterDisc = NULL;
    free(iterDisc);
    iter = NULL;
    free(iter);

    return ;
}

void removerMateria(LED **discHead, LEA **alunoHead) {
    showLEDs(discHead);
    printf("Escolha a Materia que deseja remover por Index: ");
    int opt;
    LED *iter = *discHead;
    scanf("%d",&opt);
    //
    int max_index = iter->index;
    if(opt > max_index) return ;
    // 
    while(iter->index != opt) iter = iter->prev;
    int removeableIndex = iter->index;
    //
    char filename[104] = "LEDfiles/LED";
    strcat(filename,iter->nome);
    remove(filename);
    //
    LEA *iterAluno = *alunoHead;
    if(iterAluno) {
        int tam = iterAluno->index + 1;
        for(int i=0;i<tam;i++) {
            removeDiscbyDiscName(&(iterAluno->discList),iter->nome);
            iterAluno = iterAluno->prev;
        }
    }
    removeLEDbyIndex(discHead, removeableIndex);
    iterAluno = NULL;
    free(iterAluno);
    iter = NULL;
    free(iter);
    
    return ;
}

void procurarPorAluno(LEA **endHead, int searchMode) {
    LEA *iter = *endHead;
    if(searchMode == NOME) {
        getchar();
        char nome[100];
        printf("Digite Por qual nome deseja Procurar: ");
        scanf("%[^\n]",nome);
        while(strcmp(iter->nome,nome)!=0) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else if(searchMode == NUMERO) {
        int numero;
        printf("Digite Por qual Numero deseja procurar: ");
        scanf("%d",&numero);
        while(iter->numero != numero) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else if(searchMode == CPF_PROF) {
        getchar();
        char cpf[12];
        printf("Digite o CPF pelo qual deseja procurar: ");
        scanf("%s",cpf);
        while(strcmp(iter->cpf,cpf)!=0) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else {
        printf("NO SEARCHMODE SELECTED!\n");
        iter = NULL;
        free(iter);
        return ;   
    }
    
    printf("%5s %6s %50s %11s\n","INDEX","NUMERO", "NOME", "CPF");
    printf("%5d %6d %50s %11s\n",iter->index,iter->numero,iter->nome, iter->cpf);
    iter = NULL;
    free(iter);
    return ;
}

void procurarPorMateria(LED **endHead, int searchMode) {
    LED *iter = *endHead;
    if(searchMode == NOME) {
        char nome[100];
        printf("Digite Por qual nome deseja Procurar: ");
        scanf("%[^\n]",nome);
        while(strcmp(iter->nome,nome)!=0) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else if(searchMode == NUMERO) {
        int numero;
        printf("Digite Por qual Numero deseja procurar: ");
        scanf("%d",&numero);
        while(iter->numero != numero) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else if(searchMode == CPF_PROF) {
        char prof[100];
        printf("Digite o Professor pelo qual deseja procurar: ");
        scanf("%s",prof);
        while(strcmp(iter->prof,prof)!=0) if(iter->prev) iter = iter->prev;
        else {
            iter = NULL;
            free(iter);
            return ;
        };
    } else {
        printf("NO SEARCHMODE SELECTED!\n");
        iter = NULL;
        free(iter);
        return ;   
    }
    
    printf("%5s %6s %50s %50s %8s\n","INDEX","NUMERO", "NOME", "PROF", "CREDITOS");
    printf("%5d %6d %50s %50s %8d\n",iter->index,iter->numero,iter->nome, iter->prof,iter->creditos);
    iter = NULL;
    free(iter);
    return ;
}

void mostrarAlunoseMaterias(LEA **alunoHead, LED **discHead) {
    showLEAs(alunoHead);
    showLEDs(discHead);
    return ;
}

void mostrarMateriasdeAluno(LEA **alunoHead) {
    showLEAs(alunoHead);
    int opt;
    printf("Escolha por Index: ");
    scanf("%d", &opt);
    LEA *iter = *alunoHead;
    //
    int max_index = iter->index;
    if(opt > max_index) return ;
    //
    while(iter->index != opt) iter = iter->prev;
    showDiscs(&(iter->discList));
    iter = NULL;
    free(iter);
}

void mostrarAlunosdeMateria(LED **discHead) {
    showLEDs(discHead);
    int opt;
    printf("Escolha por Index: ");
    scanf("%d", &opt);
    LED *iter = *discHead;
    //
    int max_index = iter->index;
    if(opt > max_index) return ;
    //
    while(iter->index != opt) iter = iter->prev;
    showAlunos(&(iter->alunoList));
    iter = NULL;
    free(iter);
}
