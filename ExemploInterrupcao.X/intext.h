#ifndef	INTEXT_H_
#define INTEXT_H_

// ============================================================================================ //
//						BIBLIOTECA PARA USO DE INTERRUPÇÃO EXTERNA								//
//																								//
//	ESCOLA SENAI "A. JACOB LAFER"																//
//	CURSO TÉCNICO DE ELETROELETRÔNICA															//
//	DISCIPLINA: DESET																			//
//	DATA: 02/11/2016																			//
//	REVISÃO: A																					//
// ============================================================================================	//
#include <xc.h>

#define LIGA 	1
#define DESLIGA 0

// ============================================================================================	//
//					SUB-ROTINA DE INICIALIZAÇÃO DA INTERRUPÇÃO EXTERNA							//
// ============================================================================================	//
void IntExterna(int opcao){
	TRISBbits.TRISB0 = 1;			// Determina B0 como entrada

	INTCON2bits.INTEDG0 = 1;		// Configura borda (1: subida; 0: descida) (p.100 do datasheet)
	//INTCON2bits.RBIP = 1; 		// Define a interrupção externa como de alta prioridade (p.100 do datasheet)

	RCONbits.IPEN = 1; 				// Habilita prioridade de interrupções (p. 108 do datasheet)
									// Não necessário para INT0 (já é de alta prioridade)	
				
	if(opcao == LIGA){

		INTCONbits.INT0IE = 1;		// Habilita interrupção externa por INT0 (RB0) (p. 99 do datasheet)
		INTCONbits.GIEH = 1;		// Habilita interrupções de alta prioridade (p. 99 do datasheet)
		//INTCONbits.RBIE = 1;		// Habilita interrupção por alterações na porta RB (p. 99 do datasheet)
		INTCONbits.INT0F = 0;		// Zera o flag de interrupção (p. 99 do datasheet)
	}
	else if(opcao == DESLIGA){
		INTCONbits.INT0IE = 0;		// Desabilita interrupção externa por INT0 (RB0) (p. 99 do datasheet)
		INTCONbits.GIEH = 0;		// Desabilita interrupções de alta prioridade (p. 99 do datasheet)
		//INTCONbits.RBIE = 0;		// Habilita interrupção por alterações na porta RB (p. 99 do datasheet)
	}
}

// ============================================================================================	//
#endif