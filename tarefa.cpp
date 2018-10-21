#include "tarefa.h"
#include "stdio.h"
#include "stdlib.h"



Lista_Tarefas L1;
uint16_t id;

volatile uint32_t contador;


void delay_ms (uint32_t t)
{
	
  	
	contador=t;
	while (contador>0);
}

extern "C" 
void RIT_IRQHandler(void (*f)(void))
{

    LPC_RIT->RICTRL |= 1;
    
    if (contador >=100) contador-=100;
    else contador=0;
     
   percorrer_lista();

} 

void desabilita_int(void)
{
    NVIC_DisableIRQ(RIT_IRQn);
}

void habilita_int(void)
{
    NVIC_EnableIRQ(RIT_IRQn);
}
void start ( void )
{

    // configura o tratador para disparar a cada TIC unidades
    // de tempo.
    LPC_SC->PCONP    |= (1<<16);
    LPC_SC->PCLKSEL1 |= ((1<<26) & (1<<27)); 
    LPC_RIT->RICOUNTER = 0;    
    LPC_RIT->RICOMPVAL = 12500*2*TIC;  
    LPC_RIT->RICTRL |= 2;    
    LPC_RIT->RICTRL |= 8;
    NVIC_SetPriority(RIT_IRQn, 31);
    
    habilita_int();
    id=0;
    L1.inicio = NULL;
    
}

void percorrer_lista ( void )
{
	struct celula_t * aux;
	//extern Lista_Tarefas L1;
	// varre a lista, decrementa o tempo de cada tarefa
	// se chegou a zero, reinicia o tempo e dispara a execucao
	// da funcao

	aux = L1.inicio;
	
	while (aux != NULL)
	{
		if (aux->contagem >=TIC)
		{
			// atualizao tempo
			aux->contagem-=100;
		}
		else {
			// dispara a funcao
			aux->contagem = aux->periodo;
			aux->funcao();
		}	
		
		aux = aux->proximo;
	}	
	
}

int criar_evento (int tempo_ms, void (*funcao)(void) )
{
	struct celula_t * aux;
	desabilita_int();
	int valor = id;
	id++;
	//aloca mais um elemento na lista encadeada, para faciliar
	// aloca no inicio da lista,

	aux = (struct celula_t *) malloc ( sizeof(struct celula_t)  );
	//aux ponteiro funcao vai receber o enderoco da funcao que ela vai executar
	aux->funcao = funcao;
	// periodo vai receber o tempo em ms
	aux->periodo = tempo_ms;
	// contagem vai começar com tempo_ms
	aux->contagem= tempo_ms;
	// id valor vai ser o id 
	aux->id = valor;
	// 
	aux->proximo = L1.inicio;

	L1.inicio = aux;

	habilita_int();
	  
	return valor;
}

void remover_evento(uint16_t id)
{
	struct celula_t *aux, *ant=NULL;
	aux = L1.inicio;
	desabilita_int();
	
	while (aux != NULL)
	{
		// verifica se é o id que quer remover se não for eu
		// pulo um pra frente
		if (aux->id == id)
		{
			//L1.inicio é diferente e aux
			if (L1.inicio != aux)
			{
				ant->proximo = aux->proximo;
				free(aux);
			}
			else {
				L1.inicio = aux->proximo;
				free(aux);
			}
			habilita_int();
			return;
		}
		//ant vai estar 1 atras do auxiliar
		ant = aux;
		//aux vai receber proximo
		aux = aux->proximo;

	}
	habilita_int();
}






