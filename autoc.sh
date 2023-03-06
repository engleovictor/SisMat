# !/bin/bash

gcc src/Aluno.c -o Aluno.o -c
gcc src/Disc.c -o Disc.o -c
gcc src/ListEnc.c -o ListEnc.o -c
gcc src/SisMat.c -o SisMat.o -c

gcc main.c Aluno.o Disc.o ListEnc.o SisMat.o -o programa