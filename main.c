#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/SisMat.h"

int main() {
    LEA *alunoHead = loadLEAsFromText("LEA.txt");
    LED *discHead  = loadLEDsFromText("LED.txt");
    int opcao;
    do {
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Cadastrar materia\n");
        printf("3 - Cadastrar aluno em materia\n");
        printf("4 - Remover aluno\n");
        printf("5 - Remover materia\n");
        printf("6 - Remover aluno de materia\n");
        printf("7 - Procurar por aluno\n");
        printf("8 - Procurar por materia\n");
        printf("9 - Mostrar\n");
        printf("0 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarAluno(&alunoHead);
                break;
            case 2:
                cadastrarMateria(&discHead);
                break;
            case 3:
                cadastrarAlunoEmMateria(&alunoHead, &discHead);
                break;
            case 4:
                removerAluno(&alunoHead, &discHead);
                break;
            case 5:
                removerMateria(&discHead, &alunoHead);
                break;
            case 6:
                removerAlunoDeMateria(&discHead);
                break;
            case 7:
                procurarPorAluno(&alunoHead, 0);
                break;
            case 8:
                procurarPorMateria(&discHead, 0);
                break;
            case 9:
                showLEAs(&alunoHead);
                showLEDs(&discHead);
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    saveLEAInFile(&alunoHead, "LEA.txt");
    saveLEDInFile(&discHead,  "LED.txt");

    return 0;
}
