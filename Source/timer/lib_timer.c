/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		This function allows enabling a timer by setting the first bit (bit 0) of the Timer Control Register.
**
** parameters:			timer number: 0 or 1
** Returned value:	None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 1;
  }
  else if (timer_num == 1)
  {
	LPC_TIM1->TCR = 1;
  }
	else if (timer_num == 2)
	{
	LPC_TIM2->TCR = 1;
	}
	else
	{
	LPC_TIM3->TCR = 1;
	}
	
  return;
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		This function disables a timer by clearing the first bit (bit 0) of the Timer Control Register.
**
** parameters:			timer number: 0 or 1
** Returned value:	None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 0 )
  {
	LPC_TIM0->TCR = 0;
  }
  else if (timer_num == 1)
  {
	LPC_TIM1->TCR = 0;
  }
	else if (timer_num == 2)
	{
	LPC_TIM2->TCR = 0;
	}
	else
	{
	LPC_TIM3->TCR = 0;
	}
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		This function resets a timer by clearing the second bit (bit 1) of the Timer Control Register.
**
** parameters:			timer number: 0 or 1
** Returned value:	None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 0 )
  {
	regVal = LPC_TIM0->TCR;
	regVal |= 0x02;
	LPC_TIM0->TCR = regVal;
  }
  else if (timer_num == 1)
  {
	regVal = LPC_TIM1->TCR;
	regVal |= 0x02;
	LPC_TIM1->TCR = regVal;
  }
	else if (timer_num == 2)
	{
	regVal = LPC_TIM2->TCR;
	regVal |= 0x02;
	LPC_TIM2->TCR = regVal;
	}
	else
	{
	regVal = LPC_TIM3->TCR;
	regVal |= 0x02;
	LPC_TIM3->TCR = regVal;
	}
  return;
}
/******************************************************************************
** Function name:			init_timer
**
** Descriptions:			Timer Configurations.
**
** parameters:				A lot
** Returned value:		None
**
******************************************************************************/
uint32_t init_timer ( uint8_t timer_num, uint32_t Prescaler, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval )
{
  if ( timer_num == 0 )
  {
		LPC_TIM0-> PR = Prescaler;						/* Prescaler configuration */
		
		if (MatchReg == 0){
			LPC_TIM0->MR0 = TimerInterval;			/* Timer 0 Match Register configuration. */
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg;			/* Match Control Register Configuration */
		}
		else if (MatchReg == 1){
			LPC_TIM0->MR1 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 2){
			LPC_TIM0->MR2 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg;	
		}
		else if (MatchReg == 3){
			LPC_TIM0->MR3 = TimerInterval;
			LPC_TIM0->MCR |= SRImatchReg << 3*MatchReg;	
		}
	NVIC_EnableIRQ(TIMER0_IRQn);				/* enable timer interrupts*/
	NVIC_SetPriority(TIMER0_IRQn, 8);		/* Priority configuration in interrupt handling: higher value (lower priority), lower value (higher priority) */
	return (0);
  }
  else if ( timer_num == 1 )
  {
		LPC_TIM1-> PR = Prescaler;
		
		if (MatchReg == 0){
			LPC_TIM1->MR0 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 1){
			LPC_TIM1->MR1 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 2){
			LPC_TIM1->MR2 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg;	
		}
		else if (MatchReg == 3){
			LPC_TIM1->MR3 = TimerInterval;
			LPC_TIM1->MCR |= SRImatchReg << 3*MatchReg;	
		}		
	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, 2);	/* less priority than buttons and timer0*/
	return (0);
  }
// TIMER 2
	  else if ( timer_num == 2 )
  {
		LPC_TIM2-> PR = Prescaler;
		
		if (MatchReg == 0){
			LPC_TIM2->MR0 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 1){
			LPC_TIM2->MR1 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 2){
			LPC_TIM2->MR2 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg;	
		}
		else if (MatchReg == 3){
			LPC_TIM2->MR3 = TimerInterval;
			LPC_TIM2->MCR |= SRImatchReg << 3*MatchReg;	
		}		
	NVIC_EnableIRQ(TIMER2_IRQn);
	NVIC_SetPriority(TIMER2_IRQn, 0);	/* less priority than buttons and timer0*/
	return (0);
  }
// TIMER 3
	  else if ( timer_num == 3 )
  {
		LPC_TIM3-> PR = Prescaler;
		
		if (MatchReg == 0){
			LPC_TIM3->MR0 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 1){
			LPC_TIM3->MR1 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg;			
		}
		else if (MatchReg == 2){
			LPC_TIM3->MR2 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg;	
		}
		else if (MatchReg == 3){
			LPC_TIM3->MR3 = TimerInterval;
			LPC_TIM3->MCR |= SRImatchReg << 3*MatchReg;	
		}		
	NVIC_EnableIRQ(TIMER3_IRQn);
	NVIC_SetPriority(TIMER3_IRQn, 0);	/* less priority than buttons and timer0*/
	return (0);
  }

  return (1);
}

/******************************************************************************
** Function name:			read_timer
**
** Descriptions:			Return timer counter
**
** parameters:				Timer number
** Returned value:			Timer count
**
******************************************************************************/

uint32_t read_timer(uint8_t timer_num) {
    switch (timer_num) {
        case 0:
            return LPC_TIM0->TC; 
        case 1:
            return LPC_TIM1->TC; 
        case 2:
            return LPC_TIM2->TC; 
        case 3:
            return LPC_TIM3->TC; 
        default:
            return 0; 
    }
}

/******************************************************************************
** Function name:			sec_to_count
**
** Descriptions:			null
**
** parameters:				Timer sec 
** Returned value:			Timer count
**
******************************************************************************/

uint32_t sec_to_count(float sec) {
    return (uint32_t)(sec * 25000000);
}

/******************************************************************************
** Function name:            count_to_sec
**
** Descriptions:             Converts a timer count value to seconds
**
** Parameters:               Timer count
** Returned value:           Timer sec
**
******************************************************************************/

float count_to_sec(uint32_t count) {
    return (float)count / (float) 25000000;
}

/******************************************************************************
** Function name:            timer_not_done
**
** Descriptions:             Check if timer still enable
**
** Parameters:               Timer number
** Returned value:           1 if timer not done; 0 in the other cases
**
******************************************************************************/

int timer_not_done(uint8_t timer_num) {
	if ( timer_num == 0 ){
		return (LPC_TIM0->TCR & (1 << 0));
  	}else if (timer_num == 1){
		return (LPC_TIM1->TCR & (1 << 0));
  	}else if (timer_num == 2){
		return (LPC_TIM2->TCR & (1 << 0));
	}else if(timer_num ==3){
		return (LPC_TIM3->TCR & (1 << 0));
	}else{
    	return 0;
	}
}

/******************************************************************************
** Function name:            timer_turnon
**
** Descriptions:             Turn on timer 2 and 3
**
** Parameters:               null
** Returned value:           null
**
******************************************************************************/

void timer_turnon(){
	LPC_SC -> PCONP |= (1 << 22);  // Turn on timer 2
	LPC_SC -> PCONP |= (1 << 23);  // Turn on timer 3
}

/******************************************************************************
**                            End Of File
******************************************************************************/