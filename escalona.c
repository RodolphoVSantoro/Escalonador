#include <stdio.h>
#include <stdlib.h>
#include "escalona.h"

void readProcessFile(char *fname, listaProcesso** entrada, listaProcesso ** entradaPrio){
	FILE *arq = fopen(fname, "r");
	if(arq==NULL){
		printf("Erro ao ler arquivo de entrada\n");
		exit(1);
	}
	int num[5], cont=0, r;
	Processo *p;
	do{
		r=1;
		for(int i=0;i<5 && r==1;i++){
			r = fscanf(arq, "%d, ", &num[i]);
		}
		if(r==1){
			p = (Processo*)malloc(sizeof(Processo));
			p->start = num[0];
			p->prio = num[1];
			p->totalTime = num[2];
			p->size = num[3];
			p->nDiscos = num[4];
			p->id=-1;
			p->time=0;
			p->posMem=-1;
			if(p->prio==PRIO){
				(*entradaPrio) = insereOrdem(*entradaPrio, p);
			}
			else{
				(*entrada) = insereOrdem(*entrada, p);
			}
		}
	}while(r==1);
	fclose(arq);
}

char memDisponivel(int posMem){
	if(posMem>=0)
		return 1;
	return 0;
}

int buscaMem(int blocosMem[1600], int size){
	int p1=0, p2=0;
	while(p2<1600 && p2 - p1 < ((size/10)+1)){
		p2++;
		if(blocosMem[p2]!=LIVRE){
			p1=p2;
		}
	}
	return p1;
}

void alocaMem(int blocosMem[1600], int posMem, int size, int id){
	for(int i=0;i<(size/10)+1;i++){
		blocosMem[i+posMem]=id;
	}
}
