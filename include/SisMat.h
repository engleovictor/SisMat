#ifndef SISMAT_H
#define SISMAT_H

#include "./ListEnc.h"

int cadastrarAluno(LEA **endHead);
int cadastrarMateria(LED **endHead);
int cadastrarAlunoEmMateria(LEA **alunoHead, LED **discHead);
int removerAluno(LEA **alunoHead, LED **discHead);
int removerMateria(LED **discHead, LEA **alunoHead);
int removerAlunoDeMateria(LED **discHead, LEA **alunoHead);
int AlunoEmPeriodo(LEA **endHead);
int MateriaEmPeriodo(LED **endHead);
int mostrarAlunoseMaterias(LEA **alunoHead, LED **discHead);
int mostrarMateriasdeAluno(LEA **alunoHead);
int mostrarAlunosdeMateria(LED **discHead);
int possiveisPeriodosAluno(LEA **endHead);
int possiveisPeriodosMateria(LED **endHead);

#endif /* SISMAT_H */
