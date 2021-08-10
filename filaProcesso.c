#include <stdlib.h>
#include <stdio.h>
#include "processo.h"

filaProcesso *criaFila(){
	filaProcesso *f = (filaProcesso*)malloc(sizeof(filaProcesso));
	f->frst = f->last = NULL;
	return f;
}

void addFila(filaProcesso *f, Processo *p){
	listaProcesso *node = (listaProcesso*)malloc(sizeof(listaProcesso));
	node->p=p;
	node->prox=NULL;
	if(vazio(f)){
		f->frst=f->last=node;
	}
	else{
		f->last->prox=node;
		f->last=node;
	}
}

void retiraFirst(filaProcesso *f){
	if(!vazio(f)){
		listaProcesso *tmp = f->frst;
		f->frst = tmp->prox;
		free(tmp);
		if(f->frst==NULL)
			f->last=NULL;
	}
}

char vazio(filaProcesso *f){
	if(f->frst==NULL && f->last==NULL)
		return 1;
	return 0;
}

void imprimeFila(filaProcesso *f){
	listaProcesso *tmp = f->frst;
	while(tmp!=NULL){
		printProcesso(tmp->p);
		printf("\n");
		tmp=tmp->prox;
	}
}