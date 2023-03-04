# SisMat

## Not Completed!!
 - procurarPorAluno()
 - procurarPorMateria()
 - There are some commented lines where we should "Verificar se é possível".

## Compiler

gcc (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

## Using SisMat

First clone SisMat Repo.

    $ git clone https://github.com/engleovictor/SisMat

Then:

    $ cd SisMat

    $ mkdir LEAfiles LEDfiles

compile:
 - Aluno.c
 - Disc.c
 - ListEnc.c

    $ gcc -o Aluno.o src/Aluno.c -c

    $ gcc -o Disc.o src/Disc.c -c
    
    $ gcc -o ListEnc.o src/ListEnc.c -c

Now compile main:

    gcc main.c Aluno.o Disc.o ListEnc.o -o SisMat

Finally:

    $ ./SisMat