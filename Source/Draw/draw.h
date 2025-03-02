#ifndef __DRAW_H
#define __DRAW_H

#include "stdio.h"
#include "stdlib.h"
#include "GLCD/GLCD.h"
#include "math.h"


#define PRIMARY_COLOR   Blue
#define SECONDARY_COLOR	Black
#define TEXT_COLOR White
#define NP_COLOR  0xFFFFFF 
#define PP_COLOR	Red
#define CELL_SIZE    9     
#define GHOST_CHASE_COLOR Green
#define GHOST_FRIGHTENED_COLOR Blue

void draw_square(int mat_x, int mat_y, int map_x, int map_y, int dimension, int color);
void draw_life(int life_x, int life_y, int lifes);
void draw_circle(int mat_x, int mat_y,int map_x,int map_y, int r,int dimension, int color);
void draw_scgotext(uint16_t pos_x, uint16_t pos_y, uint16_t text_color, uint16_t bg_color);
void draw_score(uint16_t pos_x, uint16_t pos_y,uint16_t text_color, uint16_t bg_color, int score);
void draw_timer(uint16_t pos_x, uint16_t pos_y,uint16_t text_color, uint16_t bg_color, int time);
void draw_wall(int mat_x, int mat_y, int map_x, int map_y, int dimension, int color);
void draw_pacman(int mat_x, int mat_y,int map_x, int map_y, int direction);
void draw_ghost(int mat_x, int mat_y,int map_x, int map_y, int color);
#endif