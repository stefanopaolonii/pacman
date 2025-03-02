#ifndef __ASTAR_H
#define __ASTAR_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Game/game.h"

#define MAX_NODES (ROWS*COLS)

typedef struct Node {
    map_pos pos;      
    int g;          
    int h;          
    int f;          
    struct Node* parent;
} Node;


int heuristic(map_pos a, map_pos b);
Node* aStar(map_pos start, map_pos goal);
int aisValid(int x, int y);
void aggiornaPercorsoFantasma(map_pos *fantasmaPos, map_pos pacManPos);

#endif