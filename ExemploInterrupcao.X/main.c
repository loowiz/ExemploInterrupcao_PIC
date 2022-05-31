/*=======================================================
					SENAI A. Jacob Lafer
					====================

Nome do projeto:	Interrup��o Externa - INT0
Vers�o:				1.0x
�ltima revis�o:		29/06/2020
Cliente:			SENAI
Desenvolvimento:	Luiz Ricardo Bitencourt

Descritivo Funcional:
Teste de funcionamento de interrup��o externa.

Inputs:
- RB0 - Chave

Outputs:
- RB2 - Display RS
- RB3 - Display E
- RD4-RD7 - Display Data
=========================================================*/

//======================================================
// Bibliotecas
//======================================================
#include <xc.h>
#include "lcd_4vias.h"
#include "intext.h"

// =====================================================
// CONFIGURA��ES DO MICROCONTROLADOR
// =====================================================
#pragma config  FOSC    = HS
#pragma config  PLLDIV  = 1
#pragma config  CPUDIV  = OSC1_PLL2
#pragma config  USBDIV  = 1
#pragma config  BORV    = 0
#pragma config  WDTPS   = 1
#pragma config  MCLRE   = ON
#pragma config	PWRT=ON, LVP=OFF, IESO=OFF, WDT=OFF, PBADEN=OFF, BOR=OFF
#pragma config  CCP2MX=ON, LPT1OSC=OFF, ICPRT=OFF, XINST=OFF, VREGEN=OFF
#pragma config  CP0=OFF, CP1=OFF, CP2=OFF, CP3=OFF, CPB=OFF, CPD=OFF, WRTD = OFF
#pragma config  WRT0=OFF, WRT1=OFF, WRT2=OFF, WRT3=OFF, WRTC = OFF, WRTB = OFF
#pragma config  EBTR0=OFF, EBTR1=OFF, EBTR2=OFF, EBTR3=OFF, EBTRB=OFF

//======================================================
// Defini��es de Hardware
//======================================================
#define Chave	PORTBbits.RB0

//======================================================
// Declara��o de Vari�veis
//======================================================
int Conta = 0;

//======================================================
// Interrup��es
//======================================================
void __interrupt() high_isr(void){      // Tratamento de interrup��o de alta prioridade (ISR)
	if(INTCONbits.INT0IF){				// Verifica flag de interrup��o externa
		INTCONbits.INT0IF = 0;			// Zera flag de interrup��o externa
		IntExterna(DESLIGA);			// Desliga interrup��o externa
        __delay_ms(30);                 // Debouncing
        while(PORTBbits.RB0);           // Debouncing
        __delay_ms(30);                 // Debouncing
        
		Conta++;						// Incrementa vari�vel de contagem
		if(Conta == 100){               // Limite de contagem
            Conta = 0;                  // Zera vari�vel de contagem a cada 100 interrup��es
        }
	}
    IntExterna(LIGA);					// Inicializa interrup��o externa
}

//======================================================
// Programa Principal
//======================================================
void main (void){
	// -------------------------------------------------
	// Configura��es iniciais
	// -------------------------------------------------
	TRISB = 0b00000011;                 // Configura dire��o dos pinos do LCD
	IniciaLCD();    					// Inicializa LCD
	IntExterna(LIGA);					// Inicializa interrup��o externa
	// -------------------------------------------------

	// -------------------------------------------------
	// Programa principal
	// -------------------------------------------------
	PosicionaLCD(1,1);
    StringLCD("   SENAI  118   ");
	PosicionaLCD(2,1);
    StringLCD("INT0:           ");

	while(1){
        PosicionaLCD(2,7);
        EscreveLCD((Conta/100)%10 + 48);
        EscreveLCD((Conta/10)%10 + 48);
        EscreveLCD(Conta%10 + 48);
	}
	// -------------------------------------------------
}
//======================================================
