#include "lpc17xx.h"

void led_off(){
		LPC_GPIO2->FIOSET1 |= (1<<1);
}

void led_on(){
		LPC_GPIO2->FIOCLR1 |= (1<<1);
}


int main (void)
{	    		
	/* by Default it is Edge Trigger
	*
	*/
	LPC_PINCON->PINSEL4 |=(1 <<24);	//  Selecting Interrupt Function EINT2 active low Sensitive
	LPC_PINCON->PINSEL4 &=~(1 <<25);	// 

	LPC_PINCON->PINSEL4&=~((1 <<19)|(1<<18));	//LED p2.9
	LPC_GPIO2->FIODIR1 |= (1<<1);							//p 2.9 direction Setting
	
NVIC_EnableIRQ(EINT2_IRQn);	

	while(1){
	       led_off();																	
		}
}

 void EINT2_IRQHandler(void)
 {
	 LPC_SC->EXTINT|=(1<<2);		//Clearing EINT2 Flag >>MUST<<
		led_on();
 }
