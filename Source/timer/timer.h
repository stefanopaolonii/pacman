/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_timer, funct_timer, IRQ_timer .c files
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#ifndef __TIMER_H
#define __TIMER_H

/* init_timer.c */

extern uint32_t init_timer( uint8_t timer_num, uint32_t Prescaler, uint8_t MatchReg, uint8_t SRImatchReg, uint32_t TimerInterval );
extern void enable_timer( uint8_t timer_num );
extern void disable_timer( uint8_t timer_num );
extern void reset_timer( uint8_t timer_num );
extern uint32_t read_timer(uint8_t timer_num);
extern uint32_t sec_to_count(float sec);
extern float count_to_sec(uint32_t count);
extern int timer_not_done(uint8_t timer_num);
extern void timer_turnon();

/* IRQ_timer.c */

extern void TIMER0_IRQHandler (void);
extern void TIMER1_IRQHandler (void);
extern void TIMER2_IRQHandler (void);
extern void TIMER3_IRQHandler (void);


#endif 
/*****************************************************************************
**                            End Of File
******************************************************************************/
