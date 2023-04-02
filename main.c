#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/SisMat.h"

#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"

int main() {
    LEA *alunoHead = loadLEAsFromText("LEA.txt");
    LED *discHead  = loadLEDsFromText("LED.txt");
    int opcao;
    printf(COLOR_YELLOW"Bem-vindo ao sistema de gestao academica!\n"COLOR_RESET);
    printf(COLOR_RED"Atencao: O programa so salva as alteracoes ao sair\n\n"COLOR_RESET);
    do {
        printf(COLOR_YELLOW "Escolha uma opcao:\n" COLOR_RESET); 
        printf("1  - Cadastrar aluno\n");
        printf("2  - Cadastrar disciplina\n");
        printf("3  - Cadastrar aluno em disciplina\n");
        printf("4  - Remover aluno\n");
        printf("5  - Remover disciplina\n");
        printf("6  - Remover aluno de disciplina\n");
        printf("7  - Periodos de alunos\n");
        printf("8  - Periodos de disciplinas\n");
        printf("0  - Salvar e Sair\n");

        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if(!cadastrarAluno(&alunoHead)) printf(COLOR_GREEN "Aluno cadastrado com sucesso!\n" COLOR_RESET);
                else printf(COLOR_RED "Aluno Repetido!!\n" COLOR_RESET);
                break;
            case 2:
                if(!cadastrarMateria(&discHead)) printf(COLOR_GREEN "Disciplina cadastrada com sucesso!\n" COLOR_RESET);
                break;
            case 3:
                if(!cadastrarAlunoEmMateria(&alunoHead, &discHead)) printf(COLOR_GREEN "Aluno cadastrado em disciplina com sucesso!\n" COLOR_RESET);
                break;
            case 4:
                if(!removerAluno(&alunoHead, &discHead)) printf(COLOR_GREEN "Aluno removido com sucesso!\n" COLOR_RESET);
                else printf(COLOR_RED "Nao ha alunos para remover!\n" COLOR_RESET);
                break;
            case 5:
                if(!removerMateria(&discHead, &alunoHead)) printf(COLOR_GREEN "Disciplina removido com sucesso!\n" COLOR_RESET);
                else printf(COLOR_RED "Nao ha disciplinas para remover!\n" COLOR_RESET);
                break;
            case 6:
                removerAlunoDeMateria(&discHead, &alunoHead);
                break;
            case 7:
                AlunoEmPeriodo(&alunoHead);
                break;
            case 8:
                if(!MateriaEmPeriodo(&discHead)) printf(COLOR_RED "Nao ha disciplinas para mostrar!\n" COLOR_RESET);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf(COLOR_RED "Opcao invalida. Tente novamente.\n" COLOR_RESET);
                break;
        }
        printf("\n");
    } while (opcao != 0);

    saveLEAInFile(&alunoHead, "LEA.txt");
    saveLEDInFile(&discHead,  "LED.txt");

    printf("Sistema encerrado. Obrigado por utilizar!\n");

    return 0; 
}
