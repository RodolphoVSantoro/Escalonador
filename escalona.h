#ifndef ESCALONA_H
#define ESCALONA_H
#include "Processo.h"
#define TIMESHARE (5)
#define LIVRE (-1)
#define USER (1)
#define PRIO (0)
#define DISCOS (4)

void readProcessFile(char *fname, listaProcesso** entrada, listaProcesso ** entradaPrio);
char memDisponivel(int posMem);
int buscaMem(int blocosMem[1600], int size);
void alocaMem(int blocosMem[1600], int posMem, int size, int id);

#endif