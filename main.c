#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/SisMat.h"

int main() {
    Aluno *alunos = loadAlunosFromText("aluno.txt");
    Disc *discs = loadDiscsFromText("disc.txt");
    Periodo *periodos = loadData("periodo.txt");
    
    int opcao;

    do {
        printf("\n---MENU---\n");
        printf("1  - Cadastrar Aluno\n");
        printf("2  - Cadastrar Matéria\n");
        printf("3  - Cadastrar Período\n");
        printf("4  - Remover Período\n");
        printf("5  - Remover Matéria\n");
        printf("6  - Remover Aluno\n");
        printf("7  - Mostrar Alunos\n");
        printf("8  - Mostrar Materias\n");
        printf("9  - Mostrar Periodos\n");        
        printf("10 - Acessar Periodo\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno(&alunos);
                break;
            case 2:
                cadastrarMateria(&discs);
                break;
            case 3:
                cadastrarPeriodo(&periodos);
                break;
            case 4:
                removerPeriodo(&periodos);
                break;
            case 5:
                removerMateria(&discs, &periodos);
                break;
            case 6:
                removerAluno(&alunos, &periodos);
                break;
            case 7:
                showAlunos(&alunos);
                break;
            case 8:
                showDiscs(&discs);
                break;
            case 9:
                showPeriodos(&periodos);
                break;
            case 10:
                if(!periodos) {
                    printf("Nenhum Periodo Cadastrado\n");
                    break;
                }
                showPeriodos(&periodos);
                int opt;
                printf("Escolha Qual periodo acessar: ");
                scanf("%d",&opt);
                if(opt > periodos->index) {
                    printf("Nao ha esse periodo!\n");
                    break;
                }
                while(periodos->index != opt) periodos = periodos->prev; 
                opt = 1;
                    do {
                        printf("\n---MENU - PERIODO: %s\n",periodos->data);
                        printf("1 - Cadastrar Matéria em Período\n");
                        printf("2 - Cadastrar Aluno em Matéria\n");
                        printf("3 - Remover Aluno de Matéria\n");
                        printf("4 - Remover Matéria de Período\n");
                        printf("5 - Mostar Materias\n");
                        printf("4 - Remover Matéria de Período\n");
                        printf("0 - Sair p/ Menu Principal\n");

                        printf("Escolha uma opção: ");
                        scanf("%d", &opt);

                        switch (opt) {
                            case 1:
                                cadastrarMateriaemPeriodo(&discs, &periodos);
                                break;
                            case 2:
                                cadastrarAlunoemMateria(&alunos, &periodos);
                                break;
                            case 3:
                                removerAlunoDeMateria(&periodos);
                                break;
                            case 4:
                                removerMateriadePeriodo(&periodos);
                                break;
                            case 5:
                                showDiscs(&(periodos->discList));
                                break;
                            case 0:
                                printf("Saindo para Menu Principal.\n");
                                break;
                            default:
                                printf("Opção inválida!\n");
                                break;
                        }

                    } while (opt != 0);
                    if(periodos) while(periodos->next) periodos = periodos->next;
                    break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 0);

    saveAlunoInFile(&alunos,"aluno.txt");
    saveDiscInFile(&discs,"disc.txt");
    saveData(&periodos,"periodo.txt");
    
    return 0;
}
