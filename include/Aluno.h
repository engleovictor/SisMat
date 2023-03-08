#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno {
    int numero;
    char nome[100];
    char cpf[12];
    struct aluno *next;
    struct aluno *prev;
    int index;
} Aluno;

Aluno *newAluno(int numero, char *nome, char *cpf, Aluno *prev);
void removeAlunobyIndex(Aluno **endHead, int index);
void showAlunos(Aluno **endHead);
Aluno *loadAlunosFromText(char *filename);
void saveAlunoInFile(Aluno **endHead, char *filename);
void removeAlunobyCPF(Aluno **endHead, char *cpf);

#endif /* ALUNO_H */