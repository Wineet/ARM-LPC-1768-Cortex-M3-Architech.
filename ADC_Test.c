#include<LPC17xx.h>

/* V1.1
* ADC Scanning and posting Data ON UART*/

void led_off(){
		LPC_GPIO2->FIOSET1 |= (1<<1);
}


void led_on(){
		LPC_GPIO2->FIOCLR1 |= (1<<1);
}


void delay()
{
	 int i,j;
   for(i=0;i<5000;i++)
			for(j=0;j<1000;j++);
}

/* UART Functions*/

void uart_send_ch( unsigned char data){			//Send a char 		

	while(!(LPC_UART3->LSR & (1<<5)));			// Wait Upto LAst Transmission to complete
	LPC_UART3->THR=data;

}

unsigned char uart_rec()
{
	unsigned char data;
          while(!(LPC_UART3->LSR & (1<<0)));			//Receive Polling 
       data=LPC_UART3->RBR;	
       return data;

}

void uart_send_str( unsigned char *ptr){			//Send a String 		

	while(*ptr)
	{
	while(!(LPC_UART3->LSR & (1<<5)));			// Wait Upto LAst Transmission to complete
	LPC_UART3->THR=*ptr;
		ptr++;
	}
	
}


/* Initialization is  common for Interrupt and Polling*/

void uart_int()
{
LPC_PINCON->PINSEL0|=(1<<1)|(1<<3);				//RX3 TX3 Setting
	
	LPC_SC->PCONP |=(1<<25);									//PowerUp UART 3
	LPC_SC->PCLKSEL1 &= (~(1<<18)|(1<<19));		// UART PCLK=CCLK/4
	LPC_UART3->LCR|=(1<<7);									  // Enable DLL and DLM Access
	//Baud Rate
	LPC_UART3->DLL=144;
	LPC_UART3->DLM=0;
	LPC_UART3->FDR =0xF2;										  // Fractional Division Adjust for accuracy
	//
	
	LPC_UART3->LCR |=(1<<0)|(1<<1);					 // 8 bit char length
	LPC_UART3->LCR &=~ (1<<7);							 // Disabling bit to do read Write operation
}



void main()
{
	unsigned int adc_val;
	
	LPC_PINCON->PINSEL4&=~((1 <<19)|(1<<18));	    //LED p2.9
	LPC_GPIO2->FIODIR1 |= (1<<1);							   //p 2.9 direction Setting
		
	LPC_SC->PCONP|=(1<<12);										   //pOWERING up ADC module
  LPC_SC->PCLKSEL0 &= (~(1<<25)|(1<<24));		   // clock/4 ~ 100Mhz/4= 25Mhz
	
	LPC_PINCON->PINSEL1 |=(1<<18);							// Setting ADC Function for AD0.2 --- P0.25
 		
	uart_int();																		// uart Init.
	
	char arr[10];
	while(1)
	{
	 LPC_ADC->ADCR |=(1<<21);										// PDN ADC Is Operational
	 LPC_ADC->ADCR |=(1<<2);									  // Channel 2 selected
   LPC_ADC->ADCR |=(1<<8);										// ADC_CLk/2  12.5Mhz max Freq 13Mhz
	
	 LPC_ADC->ADCR |=(1<<24);										// Start Of Conversion	
	
	while(!(LPC_ADC->ADGDR & (1<<31)));					// Polling to wait to Conversion Complete
	adc_val=(unsigned int)LPC_ADC->ADGDR;
	adc_val=(adc_val>>3);													
	adc_val=adc_val&0x00000FFF;
	
	  LPC_ADC->ADCR &=~(1<<24);									// Stop Of Conversion	
		LPC_ADC->ADCR &=~(1<<21);									// Power Down ADC	
		
		
		  sprintf(arr, "%d\0", adc_val);					// converting value into string for display purpose 
	    uart_send_str(arr);											// send Value to uart
		  uart_send_str("\r\n");									// to go to next line
		  delay();																// delay To View values
	}
}
