#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/ListEnc.h"

// funções para cadastrar, remover e procurar alunos e matérias
void cadastrarAluno(LEA **endHead);
void cadastrarMateria(LED **endHead);
void cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead);
void removerAluno();
void removerMateria();
void removerAlunoDeMateria(LED **endHead);
void procurarPorAluno();
void procurarPorMateria();

int main() {
    // int opcao;

    // printf("### SISMAT\n\n");

    // do {
    //     printf("Escolha uma das opcoes abaixo:\n");
    //     printf("1. Cadastrar\n");
    //     printf("2. Remover\n");
    //     printf("3. Procurar\n");
    //     printf("4. Sair\n");
    //     printf("Opcao: ");
    //     scanf("%d", &opcao);

    //     switch (opcao) {
    //         case 1:
    //             printf("Escolha uma das opcoes abaixo:\n");
    //             printf("1. Cadastrar Aluno no SisMat\n");
    //             printf("2. Cadastrar Materia no SisMat\n");
    //             printf("3. Cadastrar Aluno em Materia\n");
    //             printf("4. Cadastrar Materia em Aluno\n");
    //             printf("Opcao: ");
    //             scanf("%d", &opcao);
    //             switch (opcao) {
    //                 case 1:
    //                     cadastrarAluno();
    //                     break;
    //                 case 2:
    //                     cadastrarMateria();
    //                     break;
    //                 case 3:
    //                     cadastrarAlunoEmMateria();
    //                     break;
    //                 case 4:
    //                     cadastrarMateriaEmAluno();
    //                     break;
    //                 default:
    //                     printf("Opcao invalida\n");
    //                     break;
    //             }
    //             break;
    //         case 2:
    //             printf("Escolha uma das opcoes abaixo:\n");
    //             printf("1. Remover Aluno do SisMat\n");
    //             printf("2. Remover Materia do SisMat\n");
    //             printf("3. Remover Aluno de Materia\n");
    //             printf("4. Remover Materia de Aluno\n");
    //             printf("Opcao: ");
    //             scanf("%d", &opcao);
    //             switch (opcao) {
    //                 case 1:
    //                     removerAluno();
    //                     break;
    //                 case 2:
    //                     removerMateria();
    //                     break;
    //                 case 3:
    //                     removerAlunoDeMateria();
    //                     break;
    //                 case 4:
    //                     removerMateriaDeAluno();
    //                     break;
    //                 default:
    //                     printf("Opcao invalida\n");
    //                     break;
    //             }
    //             break;
    //         case 3:
    //             printf("Escolha uma das opcoes abaixo:\n");
    //             printf("1. Procurar por Aluno\n");
    //             printf("2. Procurar por Materia\n");
    //             printf("Opcao: ");
    //             scanf("%d", &opcao);
    //             switch (opcao) {
    //                 case 1:
    //                     procurarPorAluno();
    //                     break;
    //                 case 2:
    //                     procurarPorMateria();
    //                     break;
    //                 default:
    //                     printf("Opcao invalida\n");
    //                     break;
    //             }
    //             break;
    //         case 4:
    //             printf("Encerrando programa...\n");
    //             break;
    //         default:
    //             printf("Opcao invalida\n");
    //             break;
    //     }
    // } while (opcao != 4);

    // return 0;
    
    LED *dhead = NULL;
    LEA *head = NULL;
    dhead = newLED(1337,"LAB PROG I","CEL DUARTE",100,dhead);
    dhead = newLED(1330,"MATDIS","VELOSO",120,dhead);
    head = newLEA(21032,"LEO VICTOR","01643459309",head);
    head = newLEA(21034,"LETICIA CRUZ VASCO","01613379309",head);
    dhead->alunoList = newAluno(21032,"LEO VICTOR","01643459309",dhead->alunoList);
    dhead->alunoList = newAluno(21034,"LETICIA CRUZ VASCO","01613379309",dhead->alunoList);
    dhead->prev->alunoList = newAluno(21032,"LEO VICTOR","01643459309",dhead->prev->alunoList);
    dhead->prev->alunoList = newAluno(21034,"LETICIA CRUZ VASCO","01613379309",dhead->prev->alunoList);
    showAlunos(&(dhead->alunoList));
    showAlunos(&(dhead->prev->alunoList));
    removerAluno(&head,&dhead);
    showAlunos(&(dhead->alunoList));
    showAlunos(&(dhead->prev->alunoList));
    return 0;
}

void cadastrarAluno(LEA **endHead) {
    int numero;
    char nome[100], cpf[12];
    printf("Digite seu Numero: ");
    scanf("%d", &numero);
    getchar(); // descarta o caractere de nova linha
    printf("Digite seu Nome: ");
    scanf(" %[^\n]", nome); // adiciona um espaço antes do especificador de formato
    printf("Digite seu CPF: ");
    scanf("%s", cpf);

    *endHead = newLEA(numero,nome,cpf,*endHead);
}

void cadastrarMateria(LED **endHead) {
    int numero, creditos;
    char nome[100], prof[100];
    printf("Digite seu Numero: ");
    scanf("%d", &numero);
    getchar(); // descarta o caractere de nova linha
    printf("Digite seu Nome: ");
    scanf(" %[^\n]", nome); // adiciona um espaço antes do especificador de formato
    printf("Digite seu Professor: ");
    getchar();
    scanf("%[^\n]", prof);
    printf("Digite os Creditos: ");
    scanf("%d", &creditos);

    *endHead = newLED(numero,nome,prof,creditos,*endHead);
}

void cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead) {
    int opt;
    showLEAs(alunoHead);
    LEA *iter0 = *alunoHead;
    printf("Escolha o Aluno por index: ");
    scanf("%d",&opt);
    //
    //TEM QUE VERIFICAR AQUI NESSE PASSO SE ESSE NUMERO É POSSIVEL !!!
    //
    //
    while(iter0->index != opt) iter0 = iter0->prev;

    showLEDs(discHead);
    LED *iter1 = *discHead;
    printf("Escolha a Materia por index: ");
    scanf("%d",&opt);
    //
    //TEM QUE VERIFICAR AQUI NESSE PASSO SE ESSE NUMERO É POSSIVEL !!!
    //
    //
    while(iter1->index != opt) iter1 = iter1->prev;
    iter1->alunoList = newAluno(iter0->numero,iter0->nome,iter0->cpf,iter1->alunoList);
    iter0->discList  = newDisc(iter1->numero,iter1->nome,iter1->prof,iter1->creditos,iter0->discList);
    iter0 = NULL;
    iter1 = NULL;
    free(iter0);
    free(iter1);
}

void removerAlunoDeMateria(LED **endHead) {
    showLEDs(endHead);
    printf("Escolha o Index da Materia da qual gostaria de remover o Aluno: ");
    int opt;
    scanf("%d",&opt);
    //
    // Verificar se pode!!
    //
    //
    LED *iter = *endHead;
    while(iter->index != opt) iter = iter->prev;
    showAlunos(&(iter->alunoList));
    printf("Escolha o Index do Aluno que deseja remover dessa materia: ");
    scanf("%d",&opt);
    //
    // Verificar se pode!!
    //
    //
    removeAlunobyIndex(&(iter->alunoList),opt);
    iter = NULL;
    free(iter);
}

void removerAluno(LEA **alunoHead, LED **discHead) {
    showLEAs(alunoHead);
    printf("Escolha o Aluno que deseja remover por Index: ");
    int opt;
    LEA *iter = *alunoHead;
    scanf("%d",&opt);
    //
    // Verificar se pode!
    // 
    while(iter->index != opt) iter = iter->prev; 
    LED *iterDisc = *discHead;
    int tam = iterDisc->index + 1, removeableIndex = iter->index;
    for(int i=0;i<tam;i++) {
        removeAlunobyCPF(&(iterDisc->alunoList),iter->cpf);
        iterDisc = iterDisc->prev;
    }
    iterDisc = NULL;
    free(iterDisc);
    iter = NULL;
    free(iter);
    removeLEAbyIndex(alunoHead, removeableIndex);
}

void removerMateria(LED **discHead, LEA **alunoHead) {
    showLEDs(discHead);
    printf("Escolha a Materia que deseja remover por Index: ");
    int opt;
    LED *iter = *discHead;
    scanf("%d",&opt);
    //
    // Verificar se pode!
    // 
    while(iter->index != opt) iter = iter->prev; 
    LEA *iterAluno = *alunoHead;
    int tam = iterAluno->index + 1, removeableIndex = iter->index;
    for(int i=0;i<tam;i++) {
        removeDiscbyDiscName(&(iterAluno->discList),iter->nome);
        iterAluno = iterAluno->prev;
    }
    iterAluno = NULL;
    free(iterAluno);
    iter = NULL;
    free(iter);
    removeLEDbyIndex(discHead, removeableIndex);
}

void procurarPorAluno() {}
void procurarPorMateria() {}