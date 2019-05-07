#include "lpc17xx.h"

void led_off(){
	LPC_GPIO2->FIODIR1 |= (1<<1);								//p 2.9 direction Setting
LPC_GPIO2->FIOSET1 |= (1<<1);
}

void led_on(){
	LPC_GPIO2->FIODIR1 |= (1<<1);							//p 2.9 direction Setting
LPC_GPIO2->FIOCLR1 |= (1<<1);
}


int main (void)
{	    		

unsigned int i, j;
	
	LPC_PINCON->PINSEL4&=~((1 <<24)|(1<<25));	// Switch Connected To P2.12
	LPC_GPIO2->FIODIR &= ~(1<<12);						// Making Pin As INPUT
	
	LPC_PINCON->PINSEL4&=~((1 <<19)|(1<<18));	//LED p2.9
	

	while(1){
		
		if(!(LPC_GPIO2->FIOPIN & (1<<12))){
						led_on();
		}
		else{
		led_off();
		}
	


		}
}