// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin
#include "src/LPC17xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include "digital.h"
#include <inttypes.h>

#include "tarefa.h"

volatile uint16_t statusLED0 = 0; 
volatile uint16_t statusLED1 = 0;
volatile uint16_t statusFAN = 0;

void funcao1 (void)
{
	printf("OI mundo teste \n");
	digitalWrite(PIN_4_29, statusLED0);
	statusLED0 = !statusLED0;
}


void funcao2 (void)
{
	digitalWrite(PIN_3_26, statusLED1);
	statusLED1 = !statusLED1;
}

void funcao3 (void)
{
	printf("OI mundo \n");
}

void funcao4 (void)
{
	//delay_ms(1000);
}

void funcao5 (void)
{
	digitalWrite(PIN_1_29, statusFAN);
	statusFAN = !statusFAN;
}


int main ( void ) 
{
	int id1 = 0;

	SystemInit();

	UART0_Init(9600);
	

	pinMode (PIN_3_26, OUTPUT);
	pinMode (PIN_4_29, OUTPUT);
	pinMode (PIN_1_29, OUTPUT);

	//digitalWrite(PIN_4_29, HIGH);

	start();
	id1 = criar_evento(10000, funcao1);
	criar_evento(3000, funcao2);
	//criar_evento(3000, funcao3);
	//criar_evento(1000, funcao5);
	delay_ms(35000);

	//criar_evento(3000, funcao4);

	remover_evento(id1);

	while(1){

	}

	return 0;
}

