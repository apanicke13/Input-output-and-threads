#include "lpc17xx.h"
#include "uart.h"
#include "stdio.h"
#include "GLCD.h"
#include <cmsis_os2.h>
#include "math.h"
	 
int LED_caller(){

	unsigned int newpush=1;	
	
	while(1){
		
		unsigned int push= LPC_GPIO2->FIOPIN & (1<<10);
		
		//if the button state has changed
		if(push!=newpush){
			
			newpush=push;
			if(push==0){
				
				if((LPC_GPIO1->FIOSET & (1<<28))==0)
					LPC_GPIO1->FIOSET |= 1<<28;
				else
					LPC_GPIO1->FIOCLR |= 1<<28;
			}
		}
		
		//setting the pins' direction to output
	  	LPC_GPIO1->FIODIR |= 1<<28;
		LPC_GPIO1->FIODIR |= 1<<29;
		LPC_GPIO1->FIODIR |= 1U<<31;
		LPC_GPIO2->FIODIR |= 1<<2;
		LPC_GPIO2->FIODIR |= 1<<3;
		LPC_GPIO2->FIODIR |= 1<<4;
		LPC_GPIO2->FIODIR |= 1<<5;
		LPC_GPIO2->FIODIR |= 1<<6;
			
		osThreadYield();
 }
}

int JOY_STICK()
{
	while(1){
	
		int up =0;
		int right =0;
		int down = 0;
	  int left = 0;
		int joy = 0;
		
		while(1){
	
			//assigning Joystick's bit value to variable
			up = LPC_GPIO1->FIOPIN & (1<<23);
			right = LPC_GPIO1->FIOPIN & (1<<24);
			down = LPC_GPIO1->FIOPIN & (1<<25);
			left = LPC_GPIO1->FIOPIN & (1<<26);
			joy = LPC_GPIO1->FIOPIN & (1<<20);
			
			//checking for input on the joystick and displaying output on LCD.
			if(up==0)
				GLCD_DisplayString(1,1,1,"Up    ");

			else if(down==0)
				GLCD_DisplayString(1,1,1,"Down  ");
				
			else if(right==0)
				GLCD_DisplayString(1,1,1,"Right ");
			
			else if(left==0)
				GLCD_DisplayString(1,1,1,"Left  ");
			
			else 
				GLCD_DisplayString(1,1,1,"NO DIR");
			
			
			if(joy==0)
				GLCD_DisplayString(2,1,1,"Pressed     ");
			
			else 
				GLCD_DisplayString(2,1,1,"Not Pressed ");

		}
		
		osThreadYield();
	}
}

int ANALOG_INPUT() {
	
	while(1){	
		
		//Setting and enabling the ADC
		LPC_PINCON->PINSEL1 &= 0;
		LPC_PINCON->PINSEL1 |= (1<<18);
		LPC_SC->PCONP|= 1<<12;
		LPC_ADC->ADCR = (1<<2) | (4<<8) | (1<<21);

		while(1){
			
			LPC_ADC->ADCR |= 1<<24;
			//checking if the most significant bit is 11
			while(!(LPC_ADC->ADGDR & 1U<<31)){
				
				int d= (LPC_ADC->ADGDR & 0xFFFF)>>4;
				printf("%d\n",d);	
			}
		}	
		osThreadYield();
	}	
}


int main(void){
	
	SystemInit();
	GLCD_Init();
	osKernelInitialize();
	
	//printf statement before calling them in the functions
	printf("Initialize...");
	
	//threads to call functions
	osThreadNew(ANALOG_INPUT,NULL,NULL);
	osThreadNew(JOY_STICK,NULL,NULL);
	osThreadNew(LED_caller,NULL,NULL);
	osKernelStart();
	
	//infinite loop for kernal to take over
	while(1);

}