#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"
#include "escalona.h"

void printProcesso(Processo *p){
	printf("arrival=%d,prio=%d,time=%d,size=%d,discos=%d", p->start, p->prio, p->totalTime, p->size, p->nDiscos);
}

void liberaProcesso(Processo *p){
	free(p);
}

void liberaProcessoMem(Processo *p, int blocos[1600]){
	if(p->posMem>=0){
		for(int i=0;i<(p->size/10+1);i++){
			blocos[p->posMem+i]=LIVRE;
		}
	}
	free(p);
}
