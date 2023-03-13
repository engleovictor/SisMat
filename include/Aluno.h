#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno {
    int numero;
    char nome[100];
    char cpf[12];
    struct aluno *next;
    struct aluno *prev;
    char periodo[7];
    int index;
} Aluno;

Aluno *newAluno(int numero, char *nome, char *cpf, char *periodo,Aluno *prev);
void removeAlunobyIndex(Aluno **endHead, int index);
void removeAlunobyCPF(Aluno **endHead, char *cpf);
void showAlunos(Aluno **endHead);
Aluno *loadAlunosFromText(char *filename);
void saveAlunoInFile(Aluno **endHead, char *filename);

#endif /* ALUNO_H */