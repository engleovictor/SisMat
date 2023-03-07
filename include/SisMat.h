#ifndef SISMAT_H
#define SISMAT_H

#include "./ListEnc.h"

typedef enum {
    NOME, NUMERO, CPF_PROF 
} SEARCH_MODE;

int cadastrarAluno(LEA **endHead);
int cadastrarMateria(LED **endHead);
int cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead);
int removerAluno(LEA **alunoHead, LED **discHead);
int removerMateria(LED **discHead, LEA **alunoHead);
int removerAlunoDeMateria(LED **discHead, LEA **alunoHead);
int procurarPorAluno(LEA **endHead, int searchMode);
int procurarPorMateria(LED **endHead, int searchMode);
int mostrarAlunoseMaterias(LEA **alunoHead, LED **discHead);
int mostrarMateriasdeAluno(LEA **alunoHead);
int mostrarAlunosdeMateria(LED **discHead);

#endif /* SISMAT_H */
