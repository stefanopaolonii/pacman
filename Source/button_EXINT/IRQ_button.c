#include "button.h"
#include "lpc17xx.h"


extern int down_0;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	down_0 = 1;
	NVIC_DisableIRQ(EINT0_IRQn);			/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);   /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 0);     		/* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


