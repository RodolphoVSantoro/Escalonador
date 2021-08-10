#ifndef PROCESSO_H
#define PROCESSO_H
typedef struct Processo{
	int id, start, prio, totalTime
	, time, size, nDiscos, posMem;
}Processo;

typedef struct listaProcesso{
	Processo *p;
	struct listaProcesso *prox;
}listaProcesso;

typedef struct filaProcesso{
	listaProcesso *frst, *last;
}filaProcesso;

void printProcesso(Processo *p);
void liberaProcesso(Processo *p);
void liberaProcessoMem(Processo *p, int blocos[1600]);

listaProcesso* criaLista();
/*ordena por arrival time, considerando também ordem no arquivo de entrada*/
listaProcesso* insereOrdem(listaProcesso *l, Processo *p);
listaProcesso* retiraTopo(listaProcesso *l);
void imprimeLista(listaProcesso *l);

filaProcesso *criaFila();
void addFila(filaProcesso *f, Processo *p);
void retiraFirst(filaProcesso *f);
char vazio(filaProcesso *f);
void imprimeFila(filaProcesso *f);
#endif