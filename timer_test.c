#include<LPC17xx.h>

unsigned int flag;

void led_off(){
		LPC_GPIO2->FIOSET1 |= (1<<1);
}

void led_on(){
		LPC_GPIO2->FIOCLR1 |= (1<<1);
}


void timer0_int(){
	
  LPC_SC->PCONP |=(1<<1);		//power up timer 0
	LPC_SC->PCLKSEL0 &= (~(1<<2)|(1<<3));	// SETTING BIT TO zero PLL freq/4 ~~25 Mhz  (By Defaut this are 00)
	
	
	LPC_TIM0->PR=24;				// To set presclar of 0-24 Cycles    25 prescalar
	LPC_TIM0->PC=0;
	LPC_TIM0->TC=0;					// timer Start Value Zero
	
	LPC_TIM0->CTCR &= (~(1<<1)|(1<<0));		// Selecting Timer Mode	

}
void timer0_poll(){

	   led_on();
	  //LPC_TIM0->TC=0;
	  LPC_TIM0->TCR |=(1<<0);	             		// Timer Counter Enable
	  while(LPC_TIM0->TC<1000000);
	
		LPC_TIM0->TCR |= (1<<1);								//Timer Reset
		LPC_TIM0->TCR &= ~(1<<1);				
	
  	LPC_TIM0->TCR &= ~(1<<0);								// Stop Timer	
		
		led_off();
	//LPC_TIM0->TC=0;
	LPC_TIM0->TCR |=(1<<0);	           	      	// Timer Counter Enable
	while(LPC_TIM0->TC<1000000);
		LPC_TIM0->TCR |= (1<<1);				         //Timer Reset
		LPC_TIM0->TCR &= ~(1<<1);				
  	LPC_TIM0->TCR &= ~(1<<0);								// Stop Timer	
}






void main()
{
	LPC_PINCON->PINSEL4&=~((1 <<19)|(1<<18));	//LED p2.9
	LPC_GPIO2->FIODIR1 |= (1<<1);							//p 2.9 direction Setting
	led_off();
	   
	
	   timer0_int();
     LPC_TIM0->MR0=1000000;
	   LPC_TIM0->IR|=(1<<0);											// Reset The Interrupt Flag
		 LPC_TIM0->MCR|=(1<<0);										// Interrupt Is generated when MR0 matches with TC	
	   NVIC_EnableIRQ(TIMER0_IRQn);
	   LPC_TIM0->TCR |=(1<<0);	             		// Timer Counter Enable
	while(1)
	{
			//	timer0_poll();
				
	}
}


/*Interrupt SUBROUTINE  for TIMER */

void TIMER0_IRQHandler(void){
	
//	led_on();
	
	
	LPC_TIM0->TCR |= (1<<1);					  	//Timer Reset
		LPC_TIM0->TCR &= ~(1<<1);				
	
  	LPC_TIM0->TCR &= ~(1<<0);								// Stop Timer	
    LPC_TIM0->IR|=(1<<0);										  // Reset The Interrupt flag
		
	if(flag%2==0){
		led_on();
	}
	else{
		led_off();
	}
	 flag++;
	 LPC_TIM0->TCR |=(1<<0);	 
		
}