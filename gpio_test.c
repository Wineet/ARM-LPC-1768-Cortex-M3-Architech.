#include<LPC17xx.h>
void main(){

	LPC_PINCON->PINSEL4&=~((1<<18) | (1<<19));		//GPIO COnfig 
	LPC_GPIO2->FIODIR1 |=(1<<1);										// byte Order way set direction as OUTPUT
	
	/** All Style Have Same Effect**/
	 //LPC_GPIO2->FIODIRL =0x0100;				// Half Word Notation Style	
	 //LPC_GPIO2->FIODIRH =0x0000;	
	
   //LPC_GPIO2->FIODIR =0x00000100;				// Full word Notation Style
	int i,j;
	while(1)
	{
		LPC_GPIO2->FIOCLR1 =(1<<1);
	
		  for(i=0;i<5000;i++)
			for(j=0;j<1000;j++);
	
   	LPC_GPIO2->FIOSET1 =(1<<1);

	  for(i=0;i<5000;i++)
	  for(j=0;j<1000;j++);
	}
}