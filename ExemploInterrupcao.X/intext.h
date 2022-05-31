#ifndef	INTEXT_H_
#define INTEXT_H_

// ============================================================================================ //
//						BIBLIOTECA PARA USO DE INTERRUP��O EXTERNA								//
//																								//
//	ESCOLA SENAI "A. JACOB LAFER"																//
//	CURSO T�CNICO DE ELETROELETR�NICA															//
//	DISCIPLINA: DESET																			//
//	DATA: 02/11/2016																			//
//	REVIS�O: A																					//
// ============================================================================================	//
#include <xc.h>

#define LIGA 	1
#define DESLIGA 0

// ============================================================================================	//
//					SUB-ROTINA DE INICIALIZA��O DA INTERRUP��O EXTERNA							//
// ============================================================================================	//
void IntExterna(int opcao){
	TRISBbits.TRISB0 = 1;			// Determina B0 como entrada

	INTCON2bits.INTEDG0 = 1;		// Configura borda (1: subida; 0: descida) (p.100 do datasheet)
	//INTCON2bits.RBIP = 1; 		// Define a interrup��o externa como de alta prioridade (p.100 do datasheet)

	RCONbits.IPEN = 1; 				// Habilita prioridade de interrup��es (p. 108 do datasheet)
									// N�o necess�rio para INT0 (j� � de alta prioridade)	
				
	if(opcao == LIGA){

		INTCONbits.INT0IE = 1;		// Habilita interrup��o externa por INT0 (RB0) (p. 99 do datasheet)
		INTCONbits.GIEH = 1;		// Habilita interrup��es de alta prioridade (p. 99 do datasheet)
		//INTCONbits.RBIE = 1;		// Habilita interrup��o por altera��es na porta RB (p. 99 do datasheet)
		INTCONbits.INT0F = 0;		// Zera o flag de interrup��o (p. 99 do datasheet)
	}
	else if(opcao == DESLIGA){
		INTCONbits.INT0IE = 0;		// Desabilita interrup��o externa por INT0 (RB0) (p. 99 do datasheet)
		INTCONbits.GIEH = 0;		// Desabilita interrup��es de alta prioridade (p. 99 do datasheet)
		//INTCONbits.RBIE = 0;		// Habilita interrup��o por altera��es na porta RB (p. 99 do datasheet)
	}
}

// ============================================================================================	//
#endif