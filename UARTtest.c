#include "lpc17xx.h"


int main (void)
{	 
	LPC_PINCON->PINSEL0|=(1<<1)|(1<<3);				//RX3 TX3 Setting
	
	LPC_SC->PCONP |=(1<<25);									//PowerUp UART 3
	LPC_SC->PCLKSEL1 &= (~(1<<18)|(1<<19));		// UART PCLK=CCLK/4
	LPC_UART3->LCR|=(1<<7);									// Enable DLL and DLM Access
	//Baud Rate
	LPC_UART3->DLL=144;
	LPC_UART3->DLM=0;
	LPC_UART3->FDR =0xF2;										// Fractional Division Adjust for accuracy
	//
	
	LPC_UART3->LCR |=(1<<0)|(1<<1);					// 8 bit char length
	LPC_UART3->LCR &=~ (1<<7);							// Disabling bit to do read Write operation
unsigned char data;
	
	LPC_UART3->TER |= (1<<7);
	LPC_UART3->IER |= (1<<0);
		NVIC_EnableIRQ(UART3_IRQn);
while(1)
{
																					//rebounding the Received Data..
																					/*
																				while(!(LPC_UART3->LSR & (1<<0)));			//Receive Polling 
																					data=LPC_UART3->RBR;	
																				while(!(LPC_UART3->LSR & (1<<5)));			// Wait Upto LAst Transmission to complete
																					LPC_UART3->THR=data;*/

}	
	
}


void UART3_IRQHandler(void)
{
	char x;
	    x = LPC_UART3->RBR;
	 	while(!(LPC_UART3->LSR & (1<<5)));			// Wait Upto LAst Transmission to complete
			LPC_UART3->THR=x;
}