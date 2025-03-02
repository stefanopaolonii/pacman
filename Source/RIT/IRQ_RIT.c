/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include "RIT.h"
#include "Game/game.h"

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32
#define UPTICKS 1

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down_0=0;
volatile int IntrocurrentNote=0;
volatile int GhostcurrentNote=0;
volatile int DeathcurrentNote=0;
extern DIRECTION current_direction;
extern NOTE pacman_intro[];
extern NOTE ghost_frightened[];
extern GHOST_STATE ghost_status;

void RIT_IRQHandler(void) {

    static int up=0;
	static int downj=0;
	static int left=0;
	static int right=0;

	if(game_checkpos()){
		return;
	}

    if(down_0 !=0){
		down_0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){
			switch(down_0){
				case 2:
					game_pause();
                    reset_RIT();
					break;
				default:
					break;
			}
		}
		else {
			down_0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);				/* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);    /* External interrupt 0 pin selection */
		}
	} 

    /*************************JOYSTICK UP PRESSED***************************/

	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		up++;
		switch(up){
			case 2:
                current_direction = UP;
				break;
			default:
				break;
		}
	}
	else{
		up=0;
	}

	/*************************JOYSTICK RIGHT PRESSED***************************/

	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		right++;
		switch(right){
			case 2:
                current_direction = RIGHT;
				break;
			default:
				break;
		}
	}
	else{
		right=0;
	}

	/*************************JOYSTICK LEFT PRESSED***************************/

	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		left++;
		switch(left){
			case 2:
                current_direction = LEFT;
				break;
			default:
				break;
		}
	}
	else{
		left=0;
	}

	/*************************JOYSTICK DOWN PRESSED***************************/

	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		downj++;
		switch(downj){
			case 2:
                current_direction = DOWN;
				break;
			default:
				break;
		}
	}
	else{
		downj=0;
	}
	
    if(ghost_status==FRIGHTENED){
        if(GhostcurrentNote>=GHOST_NOTES){
            GhostcurrentNote=0;
        }
        static int ticks = 0;
        if(!isNotePlaying()){
            ++ticks;
            if(ticks == UPTICKS){
                ticks = 0;
                playNote(ghost_frightened[GhostcurrentNote++]);
            }
        }
    }else if(ghost_status==CHASE){
        if(IntrocurrentNote>=INTRO_NOTES){
        IntrocurrentNote=0;
        }
        static int ticks = 0;
        if(!isNotePlaying()){
            ++ticks;
            if(ticks == UPTICKS){
                ticks = 0;
                playNote(pacman_intro[IntrocurrentNote++]);
            }
        }
    }

    reset_RIT();
    LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
