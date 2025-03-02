#include "draw.h" 
#include "Game/game.h"

extern char map[ROWS][COLS];

static int isinmat(int i, int j);
static void DrawPacman(int centerX, int centerY, int size, int direction);
static void DrawFilledCircle(int x, int y, int r, int color);
static void wall(uint16_t m_x0, uint16_t m_y0, uint16_t m_x1, uint16_t m_y1, int i, int j, uint16_t color);
static void DrawPacman(int centerX, int centerY, int size, int direction);
static void DrawGhost(int centerX, int centerY, int size, int color);

static int isinmat(int i, int j){
    if(i<0 | i>=ROWS){
        return 0;
    }
    if(j<0 | j>=COLS){
        return 0;
    }
    return 1;
}

static void wall(uint16_t m_x0, uint16_t m_y0, uint16_t m_x1, uint16_t m_y1, int i, int j, uint16_t color) {
  // Draw the top side
  if(isinmat(i-1,j)==0 | map[i-1][j]!='#'){
    LCD_DrawLine(m_x0, m_y0+1, m_x1, m_y0+1, color);
  }
  // Draw the bottom side
  if(isinmat(i+1,j)==0  | map[i+1][j]!='#'){
    LCD_DrawLine(m_x0, m_y1-1, m_x1, m_y1-1, color);
  }
  // Draw the left side
  if(isinmat(i,j-1)==0  | map[i][j-1]!='#'){
    LCD_DrawLine(m_x0, m_y0+1, m_x0, m_y1-1, color);
  }
  // Draw the right side
  if(isinmat(i,j+1)==0  | map[i][j+1]!='#'){
    LCD_DrawLine(m_x1, m_y0+1, m_x1, m_y1-1, color);
  }

}

void draw_wall(int mat_x, int mat_y, int map_x, int map_y, int dimension, int color){
    wall((mat_y * dimension) +map_x, (mat_x * dimension)+map_y, ((mat_y + 1) * dimension -1)+map_x, ((mat_x + 1) * dimension) +map_y ,mat_x,mat_y, color);
}

void LCD_FillRect(uint16_t m_x0, uint16_t m_y0, uint16_t m_x1, uint16_t m_y1, uint16_t color) {
  uint16_t i;
  for (i = m_y0; i <= m_y1; i++) {
    LCD_DrawLine(m_x0, i, m_x1, i, color);
  }
}

void draw_square(int mat_x, int mat_y, int map_x, int map_y, int dimension, int color){
    LCD_FillRect((mat_y * dimension) +map_x, (mat_x * dimension)+map_y, ((mat_y + 1) * dimension -1)+map_x, ((mat_x + 1) * dimension) +map_y , color);
}

void draw_circle(int mat_x, int mat_y,int map_x,int map_y, int r,int dimension, int color){
    DrawFilledCircle((mat_y*dimension)+4+map_x,(mat_x*dimension)+4+map_y,r,color);
}

static void DrawFilledCircle(int x, int y, int r, int color) {
    int16_t x0 = x, y0 = y;
    int16_t x1, y1;
    int16_t dx, dy;
    int16_t d;  
    x1 = 0;
    y1 = r;
    d = 3 - 2 * r;  
    while (x1 <= y1) {
        LCD_DrawLine(x0 - x1, y0 - y1, x0 + x1, y0 - y1, color); 
        LCD_DrawLine(x0 - x1, y0 + y1, x0 + x1, y0 + y1, color); 
        LCD_DrawLine(x0 - y1, y0 - x1, x0 + y1, y0 - x1, color); 
        LCD_DrawLine(x0 - y1, y0 + x1, x0 + y1, y0 + x1, color); 
        if (d < 0) {
            d += 4 * x1 + 6;
        } else {
            d += 4 * (x1 - y1) + 10;
            y1--;
        }
        x1++;
        if (x1 <= y1) {
            LCD_DrawLine(x0 - x1, y0 - y1, x0 + x1, y0 - y1, color); 
            LCD_DrawLine(x0 - x1, y0 + y1, x0 + x1, y0 + y1, color); 
        } else {
            break;
        }
    }
}

void draw_life(int life_x, int life_y, int lifes){
    int i;
    for(i=0;i<3;i++){
        draw_square(0,i,life_x,life_y,CELL_SIZE,SECONDARY_COLOR);
    }
    for(i=0;i<lifes;i++){
        draw_pacman(0,i,life_x,life_y,4);
    }
}

void draw_scgotext(uint16_t pos_x, uint16_t pos_y, uint16_t text_color, uint16_t bg_color){
    GUI_Text(pos_x, pos_y, (uint8_t *)"SCORE ", text_color, bg_color);
    GUI_Text(pos_x+100, pos_y, (uint8_t *)"GAME OVER IN  ", text_color, bg_color);	
}

void draw_score(uint16_t pos_x, uint16_t pos_y,uint16_t text_color, uint16_t bg_color, int score){
    char tmp[5];
    sprintf(tmp,"%d",score);
    GUI_Text(pos_x, pos_y, (uint8_t *)tmp, text_color, bg_color);
}
    
void draw_timer(uint16_t pos_x, uint16_t pos_y,uint16_t text_color, uint16_t bg_color, int time){
    char tmp[5];
    sprintf(tmp, "%02d",time);
    GUI_Text(210, 0, (uint8_t *)tmp, TEXT_COLOR, SECONDARY_COLOR);

}

static void DrawPacman(int centerX, int centerY, int size, int direction) {
    int r = size / 2;  // Radius of the circle
    int x, y;
    for (y = centerY - r; y <= centerY + r; y++) {
        for (x = centerX - r; x <= centerX + r; x++) {
            int dist = (int)sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
            if (dist <= r) {
                switch (direction) {
                    case 1:
                        if (y < centerY && x >= centerX - r / 2 && x <= centerX + r / 2) {
                            continue; 
                        }
                        break;
                    case 2:
                        if (y > centerY && x >= centerX - r / 2 && x <= centerX + r / 2) {
                            continue;  
                        }
                        break;
                    case 4:
                        if (x < centerX && y >= centerY - r / 2 && y <= centerY + r / 2) {
                            continue;  
                        }
                        break;
                    case 3:
                        if (x > centerX && y >= centerY - r / 2 && y <= centerY + r / 2) {
                            continue;  
                        }
                        break;
                }

                LCD_DrawLine(x, y, x, y, Yellow); 
            }
        }
    }
}

void draw_pacman(int mat_x, int mat_y,int map_x, int map_y, int direction){
    DrawPacman((mat_y*CELL_SIZE)+4+ map_x,(mat_x*CELL_SIZE)+4+map_y,6,direction);
}

void draw_ghost(int mat_x, int mat_y,int map_x, int map_y, int color){
    DrawGhost((mat_y*CELL_SIZE)+4+ map_x,(mat_x*CELL_SIZE)+4+map_y,9,color);
}

static void DrawGhost(int centerX, int centerY, int size, int color) {
    int halfSize = size / 2;
    int top = centerY - halfSize;  
    int left = centerX - halfSize;  
    LCD_DrawLine(left, top, left + size - 1, top, 0);
    LCD_DrawLine(left, top + 1, left + size - 1, top + 1, 0);
    LCD_DrawLine(left + 3, top + 2, left + 5, top + 2, color);
    LCD_DrawLine(left + 2, top + 3, left + 6, top + 3, color);
    LCD_DrawLine(left + 1, top + 4, left + 7, top + 4, color);
    LCD_DrawLine(left + 1, top + 5, left + 7, top + 5, color);
    LCD_DrawLine(left + 1, top + 6, left + 1, top + 6, color); 
    LCD_DrawLine(left + 4, top + 6, left + 4, top + 6, color);
    LCD_DrawLine(left + 7, top + 6, left + 7, top + 6, color); 
    LCD_DrawLine(left + 1, top + 7, left + 1, top + 7, color);
    LCD_DrawLine(left + 4, top + 7, left + 4, top + 7, color); 
    LCD_DrawLine(left + 7, top + 7, left + 7, top + 7, color); 
    LCD_DrawLine(left, top + 8, left + size - 1, top + 8, 0);
}