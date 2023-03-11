# !/bin/bash

gcc src/Aluno.c -o Aluno.o -c
gcc src/Disc.c -o Disc.o -c
gcc src/Periodo.c -o Periodo.o -c
gcc src/SisMat.c -o SisMat.o -c


gcc main.c Aluno.o Disc.o Periodo.o SisMat.o -o SisMatProgram
