#ifndef SISMAT_H
#define SISMAT_H

#include "./Periodo.h"

typedef enum {
    NOME, NUMERO, CPF_PROF 
} SEARCH_MODE;

int cadastrarAluno(Aluno **endHead);
int cadastrarMateria(Disc **endHead);
int cadastrarPeriodo(Periodo **endHead);
int cadastrarMateriaemPeriodo(Disc **discHead, Periodo **periodoHead);
int cadastrarAlunoemMateria(Aluno **alunoHead, Periodo **periodo);
int removerAlunoDeMateria(Periodo **periodo);
int removerMateriadePeriodo(Periodo **periodo);
int removerPeriodo(Periodo **periodos);
int removerMateria(Disc **discHead, Periodo **periodoHead);
int removerAluno(Aluno **alunoHead, Periodo **periodoHead);

#endif /* SISMAT_H */