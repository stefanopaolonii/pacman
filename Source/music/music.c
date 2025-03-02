#include "music.h"
#include "../timer/timer.h"

#define DEATH_NOTES 20

NOTE pacman_intro[] = {
   	{c2, time_semicroma}, {e2, time_semicroma}, {g2, time_semicroma}, {e2, time_semicroma},
    {g2, time_semicroma}, {a2, time_semicroma}, {g2, time_semicroma}, {e2, time_semicroma},
    {c2, time_croma}, {pause, time_croma},
    {g2, time_semicroma}, {c3, time_semicroma}, {a2, time_semicroma}, {g2, time_semicroma},
    {e2, time_semicroma}, {g2, time_semicroma}, {a2, time_semicroma}, {c3, time_semicroma},
    {g2, time_croma}, {pause, time_croma}
};

NOTE ghost_frightened[] = {
    {a2, time_croma}, {c2, time_croma},
    {d2, time_croma}, {e2, time_croma}
};

void playNote(NOTE note){
	if(note.freq != pause){
		reset_timer(2);
		init_timer(2,0,0,3, note.freq);
		enable_timer(2);
	}
	reset_timer(3);
	init_timer(3,0,0,7, note.duration);
	enable_timer(3);
}

BOOL isNotePlaying(void)
{
	return ((LPC_TIM2->TCR != 0) || (LPC_TIM3->TCR != 0));
}


