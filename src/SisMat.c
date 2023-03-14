#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/SisMat.h"

int cadastrarAluno(LEA **endHead) {
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
    
    
    if(iter) {
        int tam = iter->index + 1;
        
        if(strcmp(iter->cpf,cpf) == 0) {
            iter = NULL;
            free(iter);
            return 1;
        }
        
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

    *endHead = newLEA(numero,nome,cpf,*endHead);

    return 0;
}

int cadastrarMateria(LED **endHead) {
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

    if(iter) {
        int tam = iter->index + 1;
        
        if(strcmp(iter->prof,prof) == 0) {
            iter = NULL;
            free(iter);
            return 1;
        }
        
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

    *endHead = newLED(numero,nome,prof,creditos,*endHead);

    return 0;
}

int cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead) {
    int opt;
    showLEAs(alunoHead);
    LEA *iter0 = *alunoHead;
    printf("Escolha o Aluno por index: ");
    scanf("%d",&opt);
    //
    int max_index = iter0->index;
    if(opt > max_index) {
        iter0 = NULL;
        free(iter0);
        return 1;
    }
    //
    while(iter0->index != opt) iter0 = iter0->prev;

    showLEDs(discHead);
    LED *iter1 = *discHead;
    printf("Escolha a Materia por index: ");
    scanf("%d",&opt);
    //
    max_index = iter1->index;
    if(opt > max_index) {
        iter1 = NULL;
        iter0 = NULL;
        free(iter0);
        free(iter1);
        return 2;    
    }
    //
    while(iter1->index != opt) iter1 = iter1->prev;

    Aluno *iter = iter1->alunoList;
    if(iter) {
        int tam = iter->index + 1;
        if(strcmp(iter->cpf,iter0->cpf) == 0) {
            iter = NULL;
            iter0 = NULL;
            iter1 = NULL;
            free(iter);
            free(iter0);
            free(iter1);
            return 3;
        }
        for(int i=0;i<tam;i++) {
            if(strcmp(iter->cpf,iter0->cpf) == 0) {
                iter = NULL;
                iter0 = NULL;
                iter1 = NULL;
                free(iter);
                free(iter0);
                free(iter1);
                return 3;
            }
            iter = iter->prev;
        }
    }
    
    char periodo[7];
    printf("Digite o Periodo: ");
    scanf("%s",periodo);

    iter1->alunoList = newAluno(iter0->numero,iter0->nome,iter0->cpf,periodo,iter1->alunoList);
    iter0->discList  = newDisc(iter1->numero,iter1->nome,iter1->prof,iter1->creditos,periodo,iter0->discList);
    iter0 = NULL;
    iter1 = NULL;
    free(iter0);
    free(iter1);

    return 0;
}

int removerAlunoDeMateria(LED **discHead, LEA **alunoHead) {
    showLEDs(discHead);
    printf("Escolha o Index da Materia da qual gostaria de remover o Aluno: ");
    int opt;
    scanf("%d",&opt);
    LED *iter = *discHead;
    //
    int max_index = iter->index;
    if(opt > max_index) {
        iter = NULL;
        free(iter);
        return 1;
    }
    //
    while(iter->index != opt) iter = iter->prev;
    showAlunos(&(iter->alunoList));
    printf("Escolha o Index do Aluno que deseja remover dessa materia: ");
    scanf("%d",&opt);
    
    Aluno *aluno = iter->alunoList;
    //
    max_index = aluno->index;
    if(opt > max_index) {
        iter = NULL;
        aluno = NULL;
        free(aluno);
        free(iter);
        return 2;
    }
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

    return 0;
}

int removerAluno(LEA **alunoHead, LED **discHead) {
    showLEAs(alunoHead);
    printf("Escolha o Aluno que deseja remover por Index: ");
    int opt;
    LEA *iter = *alunoHead;

    if(!iter) {
        free(iter);
        return 1;
    }

    scanf("%d",&opt);
    //
    int max_index = iter->index;
    if(opt > max_index) {
        iter = NULL;
        free(iter);
        return 2;
    }
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

    return 0;
}

int removerMateria(LED **discHead, LEA **alunoHead) {
    showLEDs(discHead);
    printf("Escolha a Materia que deseja remover por Index: ");
    int opt;
    LED *iter = *discHead;
    if(!iter) {
        free(iter);
        return 1;
    }


    scanf("%d",&opt);
    //
    int max_index = iter->index;
    if(opt > max_index) {
        iter = NULL;
        free(iter);
        return 2;
    }
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
    
    return 0;
}

int AlunoEmPeriodo(LEA **endHead) {
    LEA *iter = *endHead;
    if(!iter) return 1;
    int opt;
    char periodo[7];
    showLEAs(&iter);
    printf("Escolha o Aluno que quer ver o Periodo: ");
    scanf("%d",&opt);
    while(iter->index != opt) iter = iter->prev;
    if(possiveisPeriodosAluno(&iter) == 1) {
        printf("Nenhuma disciplina cadastrada para este aluno\n"); 
        return 3;
    }
    else printf("Escolha o periodo que deseja: ");
    scanf("%s",periodo);
    Disc *iterDisc = iter->discList;
    if(!iterDisc) return 2;

    int jaPrinteiHeader = 0;

    if(strcmp(iterDisc->periodo,periodo) == 0) {
        printf("%5s %6s %50s %50s %8s\n","INDEX","NUMERO", "NOME", "PROF", "CREDITOS");
        printf("%5d %6d %50s %50s %8d\n",iterDisc->index,iterDisc->numero,iterDisc->nome, iterDisc->prof,iterDisc->creditos);
        jaPrinteiHeader = 1;
    }
        
    while(iterDisc->prev) {
        iterDisc = iterDisc->prev;
        if(strcmp(iterDisc->periodo,periodo) == 0)  {
            if(!jaPrinteiHeader) { 
                printf("%5s %6s %50s %50s %8s\n","INDEX","NUMERO", "NOME", "PROF", "CREDITOS");
                jaPrinteiHeader = 1; 
            }
            printf("%5d %6d %50s %50s %8d\n",iterDisc->index,iterDisc->numero,iterDisc->nome, iterDisc->prof,iterDisc->creditos);
        }
    }

    iterDisc = NULL;
    free(iterDisc);
    iter = NULL;
    free(iter);
    return 0;
}

int MateriaEmPeriodo(LED **endHead) {
    LED *iter = *endHead;
    if(!iter) return 1;
    int opt;
    char periodo[7];
    showLEDs(&iter);
    printf("Escolha a Materia que quer ver o Periodo: ");
    scanf("%d",&opt);
    while(iter->index != opt) iter = iter->prev;
    if(possiveisPeriodosMateria(&iter) == 1) {
        printf("Nenhum aluno cadastrada para esta disciplina\n");
        return 3;
    }
    else printf("Escolha o periodo que deseja: ");
    scanf("%s",periodo);
    Aluno *iterAluno = iter->alunoList;
    if(!iterAluno) return 2;

    int jaPrinteiHeader = 0;

    if(strcmp(iterAluno->periodo,periodo) == 0) {
        printf("%5s %6s %50s %11s\n","INDEX","NUMERO", "NOME", "CPF");
        printf("%5d %6d %50s %11s\n",iterAluno->index,iterAluno->numero,iterAluno->nome, iterAluno->cpf);
        jaPrinteiHeader = 1;
    }
    
    while(iterAluno->prev) {
        iterAluno = iterAluno->prev;
        if(strcmp(iterAluno->periodo,periodo) == 0)  {
            if(!jaPrinteiHeader) { 
                printf("%5s %6s %50s %11s\n","INDEX","NUMERO", "NOME", "CPF");
                jaPrinteiHeader = 1; 
            }
            printf("%5d %6d %50s %11s\n",iterAluno->index,iterAluno->numero,iterAluno->nome, iterAluno->cpf);
        }
    }

    iterAluno = NULL;
    free(iterAluno);
    iter = NULL;
    free(iter);
    return 0;
}

int mostrarAlunoseMaterias(LEA **alunoHead, LED **discHead) {
    showLEAs(alunoHead);
    showLEDs(discHead);
    return 0;
}

int mostrarMateriasdeAluno(LEA **alunoHead) {
    showLEAs(alunoHead);
    int opt;
    printf("Escolha por Index: ");
    scanf("%d", &opt);
    LEA *iter = *alunoHead;
    //
    int max_index = iter->index;
    if(opt > max_index) {
        iter = NULL;
        free(iter);
        return 1;
    }
    //

    while(iter->index != opt) iter = iter->prev;
    showDiscs(&(iter->discList));
    iter = NULL;
    free(iter);

    return 0;
}

int mostrarAlunosdeMateria(LED **discHead) {
    showLEDs(discHead);
    int opt;
    printf("Escolha por Index: ");
    scanf("%d", &opt);
    LED *iter = *discHead;
    //
    int max_index = iter->index;
    if(opt > max_index) {
        iter = NULL;
        free(iter);
        return 1;
    }
    //
    while(iter->index != opt) iter = iter->prev;
    showAlunos(&(iter->alunoList));
    iter = NULL;
    free(iter);

    return 0;
}

int possiveisPeriodosAluno(LEA **endHead) {
    Disc *iter = (*endHead)->discList;
    if(!iter) return 1;
    int tam = iter->index+1;
    char periodos[tam][8];
    int tp = 0;
    for(int i = 0; i < tam; i++){
        if(tp == 0){
            strcpy(periodos[tp],iter->periodo);
            tp++;
        }
        else{
            for(int j = 0; j < tp; j++){
                if(strcmp(periodos[j],iter->periodo) == 0){
                    break;
                } 
                if(j == tp-1) {
                    strcpy(periodos[tp],iter->periodo);
                    tp++;
                }            
            }
        }
        iter = iter->prev;
    }
    iter = NULL;
    free(iter);
    if(tp) printf("Periodos:\n");
    for(int i = 0;i < tp; i++) printf("%s\n", periodos[i]);
    return 0;
}

int possiveisPeriodosMateria(LED **endHead) {
    Aluno *iter = (*endHead)->alunoList;
    if(!iter) return 1;
    int tam = iter->index+1;
    char periodos[tam][8];
    int tp = 0;
    for(int i = 0; i < tam; i++){
        if(tp == 0){
            strcpy(periodos[tp],iter->periodo);
            tp++;
        }
        else{
            for(int j = 0; j < tp; j++){
                if(strcmp(periodos[j],iter->periodo) == 0){
                    break;
                } 
                if(j == tp-1) {
                    strcpy(periodos[tp],iter->periodo);
                    tp++;
                }
            }
        }
        iter = iter->prev;
    }

    if(tp) printf("Periodos:\n");
    for(int i = 0;i < tp; i++) printf("%s\n", periodos[i]);
    return 0;
}