#ifndef MUSIC_H
#define MUSIC_H

#include "LPC17xx.h"
//Default: 1.65
#define SPEEDUP 1.6

#define TIMERSCALER 1
#define INTRO_NOTES 20
#define GHOST_NOTES 4
#define SECOND 0x17D7840 * TIMERSCALER


typedef char BOOL;
#define TRUE 1
#define FALSE 0

typedef enum note_durations
{
	time_semibiscroma = (unsigned int)(SECOND * SPEEDUP / 64.0f + 0.5), // 1/128
	time_biscroma = (unsigned int)(SECOND * SPEEDUP / 32.0f + 0.5), // 1/64
	time_semicroma = (unsigned int)(SECOND * SPEEDUP / 16.0f + 0.5), // 1/32
	time_croma = (unsigned int)(SECOND * SPEEDUP / 8.0f + 0.5), // 1/16
	time_semiminima = (unsigned int)(SECOND * SPEEDUP / 4.0f + 0.5), // 1/4
	time_minima = (unsigned int)(SECOND * SPEEDUP / 2.0f + 0.5), // 1/2
	time_semibreve = (unsigned int)(SECOND * SPEEDUP + 0.5), // 1
} NOTE_DURATION;

typedef enum frequencies{
	a1 = 8802,      // ~55Hz
	b1 = 7835,      // ~62Hz
	c2 = 7355,      // ~65Hz
	d2 = 6541,      // ~73Hz
	e2 = 5810,      // ~82Hz
	f2 = 5486,      // ~87Hz
	g2 = 4903,      // ~98Hz
	a2 = 4441,      // ~110Hz
	a2b = 5351,     // ~103Hz
	b2 = 4500,      // ~123Hz
	c3b = 4370,     // ~127Hz
	c3 = 4240,      // ~131Hz
	d3 = 3779,      // ~147Hz
	e3 = 3367,      // ~165Hz
	f3 = 3175,      // ~175Hz
	g3 = 2834,      // ~196Hz
	a3b = 2670,     // ~208Hz
	a3 = 2525,      // ~220Hz
	b3 = 2249,      // ~247Hz
	c4 = 2120,      // ~262Hz
	d4 = 1890,      // ~294Hz
	e4 = 1684,      // ~330Hz
	f4 = 1592,      // ~349Hz
	g4 = 1417,      // ~392Hz
	a4 = 1263,      // ~440Hz
	b4 = 1125,      // ~494Hz
	c5 = 1062,      // ~523Hz
	pause = 0       // DO NOT SOUND
} FREQUENCY;

typedef struct 
{
	FREQUENCY freq;
	NOTE_DURATION duration;
} NOTE;

void playNote(NOTE note);
BOOL isNotePlaying(void);
#endif
