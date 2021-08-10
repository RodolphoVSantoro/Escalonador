#include <stdlib.h>
#include <stdio.h>
#include "processo.h"

listaProcesso* criaLista(){
	return NULL;
}

/*ordena por arrival time, considerando também ordem no arquivo de entrada*/
listaProcesso* insereOrdem(listaProcesso *l, Processo *p){
	listaProcesso *node = (listaProcesso*)malloc(sizeof(listaProcesso));
	node->p=p;
	listaProcesso *tmp = l, *ant = NULL;
	while(tmp!=NULL && tmp->p->start <= node->p->start){
		ant = tmp;
		tmp=tmp->prox;
	}
	if(tmp!=NULL && ant!=NULL){
		node->prox=tmp;
		ant->prox=node;
	}
	else if(ant==NULL){
		node->prox = l;
		l = node;
	}
	else{
		ant->prox=node;
		node->prox=NULL;
	}
	return l;
}

listaProcesso* retiraTopo(listaProcesso *l){
	if(l!=NULL){
		listaProcesso *tmp = l;
		l=l->prox;
		free(tmp);
	}
	return l;
}

void imprimeLista(listaProcesso *l){
	listaProcesso *tmp = l;
	while(tmp!=NULL){
		printProcesso(tmp->p);
		printf("\n");
		tmp=tmp->prox;
	}
}