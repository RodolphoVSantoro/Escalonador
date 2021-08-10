#include <stdio.h>
#include <stdlib.h>
#include "processo.h"
#include "escalona.h"

int main(){
	//processos não criados
	listaProcesso *entrada = criaLista(), *entradaPrio = criaLista();
	readProcessFile("processos.txt", &entrada, &entradaPrio);
	printf("Entrada:\n");
	imprimeLista(entrada);
	printf("EntradaPrio:\n");
	imprimeLista(entradaPrio);
	//fila de processos criados 
	filaProcesso *processos = criaFila(), *processosPrio = criaFila();
	Processo *processador[4];
	for(int i=0;i<4;i++)
		processador[i]=NULL;
	int t=0, id=0;
	/*blocos de aprox 10MB*/
	/*guarda o id do processo usando 
		aquele bloco*/
	int blocosMem[1600];
	for(int i=0;i<1600;i++)
		blocosMem[i]=LIVRE;
	int tempoUsado[4];
	for(int i=0; i<4; i++)
		tempoUsado[i]=0;
	int nDiscosLivres=4;
	int posMem=-1;
	int processadoresVazios=1;
	while(entrada!=NULL || entradaPrio!=NULL || !vazio(processos) || !vazio(processosPrio) || processadoresVazios == 0){
		printf("t=%d:\n", t);
		printf("\tCriacao de processos:\n");
		/*tenta colocar na fila se chegou no 
			arrival time e alocar na mem*/
		if(entradaPrio!=NULL){
			do{
				posMem = buscaMem(blocosMem, entradaPrio->p->size);
				if(entradaPrio->p->start<=t)
					printf("\t\tTentando criar processo %d\n", id);
				if(entradaPrio->p->start<=t && memDisponivel(posMem)){
					if(entradaPrio->p->nDiscos<=DISCOS){
						entradaPrio->p->id = id;
						id++;
						entradaPrio->p->posMem = posMem;
						addFila(processosPrio, entradaPrio->p);
						alocaMem(blocosMem, posMem, entradaPrio->p->size, id-1);
						printf("\t\tProcesso criado com sucesso(");
						printProcesso(entradaPrio->p);
						printf(")\n");
					}
					else{
						printf("\t\t\tImpossivel criar processo, precisa de mais discos que a quantidade do sistema\n");
						liberaProcesso(entradaPrio->p);
					}
					entradaPrio = retiraTopo(entradaPrio);
				}
				else{
					if(entradaPrio->p->start<=t){
						printf("\t\t\tImpossivel criar, sem memoria contigua Livre suficiente\n");
					}
				}
			}while(posMem!=-1 && entradaPrio!=NULL && entradaPrio->p->start<=t);
		}
		/*cria de usuario se nenhum de prioridade 
			foi ou vai ser submetido*/
		if(entrada!=NULL && (entradaPrio==NULL || entradaPrio->p->start > t)){
			do{
				posMem = buscaMem(blocosMem, entrada->p->size);
				if(entrada->p->start<=t)
					printf("\t\tTentando criar processo %d\n", id);
				if(entrada->p->start<=t && memDisponivel(posMem)){
					if(entrada->p->nDiscos<=DISCOS){
						entrada->p->id = id;
						id++;
						entrada->p->posMem = posMem;
						addFila(processos, entrada->p);
						alocaMem(blocosMem, posMem, entrada->p->size, id-1);
						printf("\t\tProcesso criado com sucesso(");
						printProcesso(entrada->p);
						printf(")\n");
					}
					else{
						printf("\t\t\tImpossivel criar processo, precisa de mais discos que a quantidade do sistema\n");
						liberaProcesso(entrada->p);
					}
					entrada = retiraTopo(entrada);
				}
				else{
					if(entrada->p->start<=t){
						printf("\t\t\tImpossivel criar, sem memoria contigua Livre suficiente\n");
					}
				}
			}while(posMem!=-1 && entrada!=NULL && entrada->p->start<=t);
		}
		printf("\tProcessando:\n");
		//escalonando
		for(int i=0;i<4;i++){
			//tem processo usando a cpu num. i
			if(processador[i]!=NULL){
				tempoUsado[i]++;
				processador[i]->time++;
				printf("\t\tProcesso %d esta %ds seguidos no processador %d\n", processador[i]->id, tempoUsado[i], i);
				if(processador[i]->totalTime==processador[i]->time){
					//acaba com o processo
					printf("\t\tProcesso %d terminou, liberando recursos\n", processador[i]->id);
					nDiscosLivres+=processador[i]->nDiscos;
					liberaProcessoMem(processador[i], blocosMem);
					tempoUsado[i]=0;
					processador[i]=NULL;
				}
				else if(tempoUsado[i]>TIMESHARE){
					//volta com o processo pra fila
					printf("\t\tProcesso %d vai retornar para a fila, liberando discos\n", processador[i]->id);
					nDiscosLivres+=processador[i]->nDiscos;
					if(processador[i]->prio==PRIO)
						addFila(processosPrio, processador[i]);
					else
						addFila(processos, processador[i]);
					processador[i]=NULL;
					tempoUsado[i]=0;
				}
			}
			if(processador[i]==NULL){
				//tentar tirar das filas
				if(!vazio(processosPrio)){
					if(processosPrio->frst->p->nDiscos<=nDiscosLivres){
						nDiscosLivres-=processosPrio->frst->p->nDiscos;
						processador[i]=processosPrio->frst->p;
						retiraFirst(processosPrio);
						printf("\t\tProcessador %d vai executar o processo %d\n", i, processador[i]->id);
					}
				}
				else if(!vazio(processos)){
					if(processos->frst->p->nDiscos<=nDiscosLivres){
						nDiscosLivres-=processos->frst->p->nDiscos;
						processador[i]=processos->frst->p;
						retiraFirst(processos);
						printf("\t\tProcessador %d vai executar o processo %d\n", i, processador[i]->id);
					}
				}
				else{
					printf("\t\tProcessador %d esta ocioso\n", i);
				}
			}
		}
		processadoresVazios=1;
		for(int i=0;i<4;i++){
			if(processador[i]!=NULL){
				processadoresVazios=0;
			}
		}
		system("PAUSE");
		t++;
	}
	free(processosPrio);
	free(processos);
	return 0;
}
