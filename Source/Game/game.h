#ifndef 	__GAME_H
#define 	__GAME_H

#include "Draw/draw.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "GLCD/GLCD.h"
#include "Draw/draw.h"
#include "CAN/CAN.h"
#include "stdio.h"

#define MAP_X 3
#define MAP_Y 30
#define ROWS 31
#define COLS 26
#define RANDOM_PILLS	6
#define NP_SCORE 10
#define PP_SCORE 50
#define LIFE_POINT 1000
#define PAUSE_TEXT "PAUSE"
#define GOVER_TEXT "GAME OVER"
#define GVICTORY_TEXT "VICTORY!"
#define COUNTDOWN 60
#define GHOST_START_DELAY 5
#define GHOST_FRIGHTENED_TIME 10
#define GHOST_SPEED_CHANGE_TIME 30
typedef enum{START,UP,DOWN,RIGHT,LEFT} DIRECTION;
typedef struct {int i; int j;} map_pos;
typedef enum{CHASE,FRIGHTENED} GHOST_STATE;

void game_init();
void game_changedirection();
void game_pause();
void game_over();
void game_timeupdate();
void game_ghostupdate();
int game_checkpos();

#endif