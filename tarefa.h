#ifndef __TAREFA__
#define __TAREFA__
#include "src/LPC17xx.h"
#include "inttypes.h"
#include "digital.h"

#define TIC 100 // 100ms

void delay_ms (uint32_t t);

struct celula_t {
	// Ponteiro para função
	void (*funcao)(void);
	// Periodo 
	uint32_t periodo;
	// Contagem
	uint32_t contagem;
	// id numero do evento
	uint16_t id;
	// ponteiro para o proximo
	struct celula_t * proximo;
};

typedef struct {
	struct celula_t * inicio;

}Lista_Tarefas;

// tinha feito global , so q falava que duplicado
// Criando uma lista 
extern Lista_Tarefas L1;
// id da lista

extern uint16_t id; /* não pode criar dois ids iguais*/

// funcação para desabilitar as interrupções
void desabilita_int(void);
// habilitar as interrupções
void habilita_int(void);

//funcção pra dar start 
void start (void);
// funcão que fica varrendo a lista, pra verificar a contagem
void percorrer_lista (void);
//adicionar uma nova tarefa na lista
int criar_evento ( int tempo_ms , void (*funcao)(void) );
//remover a tarefa pelo id 
void remover_evento( uint16_t id);



#endif
