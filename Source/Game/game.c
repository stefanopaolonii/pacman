#include "game.h"

volatile int current_pill=240;
volatile int current_life=1;
volatile int current_score=1;
volatile int tmp_score=1;
volatile int game_status=0;
volatile int h=0;
volatile int countdown=COUNTDOWN;
volatile int interrupt_per_second=5;
volatile int ghost_frightened_countdown=10;
volatile int ghost_start_time=GHOST_START_DELAY;
volatile DIRECTION current_direction=START;
volatile DIRECTION old_direction=START;
volatile map_pos pac_pos;
volatile map_pos tel_r;
volatile map_pos tel_l;
volatile map_pos ghost_pos;
volatile map_pos pac_initial_pos;
volatile map_pos ghost_initial_pos;
volatile GHOST_STATE ghost_status;
volatile char map[ROWS][COLS] = {
"##########################",
"#........................#",
"#.######################.#",
"#...........##...........#",
"#.#########.##.###.#####.#", 
"#.#########.##.###.#####.#", 
"#.#########.##.###.#####.#", 
"#.#####............#####.#", 
"#.#####.###.######.#####.#", 
"#.#####.###.######.#####.#", 
"#........................#", 
"#.###.##############.###.#", 
"#.###.##############.###.#", 
"#.....       p      .....#", 
"##### #####     ##### ####",
"l     #             #    r",
"##### #      g      # ####",
"##### ############### ####", 
"#........................#", 
"#.#########.##.#########.#", 
"#...........##...........#", 
"#.#########.############.#", 
"#.#########.############.#", 
"#.#########.############.#", 
"#.#########.############.#", 
"#...........##...........#", 
"###.#######.##.########.##",
"###.#######.##.########.##",
"###.........##..........##",
"##########################",
"##########################"
};
volatile int randompills[RANDOM_PILLS];
volatile int randompillspawn[RANDOM_PILLS];
volatile map_pos randompillpos[RANDOM_PILLS];

/**
 * Initializes the LCD display for the game.
 */
static void game_lcdinit();
static void powerpills_positiongeneration();
static void powerpillstime_generation();
static void game_map();
static void game_victory();
static void game_sendinfo();
static map_pos trovaPosizioneLontanaDaPacman(map_pos pacManPos);

/**
 * Generates random positions for power pills.
 */
static void powerpills_positiongeneration(){
	int i,j,tmp;
	srand(time(NULL));
	for(i=0; i<RANDOM_PILLS;i++){
		randompills[i]= rand() % 241;
	}
	for(i=0; i<RANDOM_PILLS;i++){
		for(j=i+1;j<RANDOM_PILLS;j++){
				if(randompills[j]<randompills[i]){
					tmp=randompills[i];
					randompills[i]=randompills[j];
					randompills[j]=tmp;
				}
		}
	}
}

/**
 * Generates random spawn times for power pills.
 */
static void powerpillstime_generation(){
	int i,j,tmp;
	srand(time(NULL));
	for(i=0; i<RANDOM_PILLS;i++){
		randompillspawn[i]= 60-(rand() % 31);
	}
	for(i=0; i<RANDOM_PILLS;i++){
		for(j=i+1;j<RANDOM_PILLS;j++){
				if(randompillspawn[j]>randompillspawn[i]){
					tmp=randompillspawn[i];
					randompillspawn[i]=randompillspawn[j];
					randompillspawn[j]=tmp;
				}
		}
	}
}

/**
 * Initializes the game by setting up power pills and the LCD display.
 */
static void game_lcdinit(){
	LCD_Clear(Black);
	game_map();
	draw_life(MAP_X,310,current_life);
	GUI_Text(103+MAP_X,136+MAP_Y, (uint8_t *)PAUSE_TEXT, Yellow, SECONDARY_COLOR);
}

/**
 * Initializes the game by generating power pills and setting up the LCD display.
 */
void game_init(){
	powerpills_positiongeneration();
	powerpillstime_generation();
	game_lcdinit();
	enable_RIT();
}

/**
 * Draws the game map on the LCD display.
 */
static void game_map() {
	volatile int i,j,k=0,count=0;
	for ( i = 0; i < ROWS; i++) {
		for ( j = 0; j < COLS; j++) {
			switch (map[i][j]) {
				case '#':
					draw_wall(i,j,MAP_X,MAP_Y,CELL_SIZE,Blue);
					break;
				case '.': 
					if(k<RANDOM_PILLS && randompills[k]==count){
						randompillpos[k].i=i;
						randompillpos[k].j=j;
						k++;
					}
					draw_circle(i,j,MAP_X,MAP_Y,1,CELL_SIZE,NP_COLOR);
					count++;
					break;
				case 'p':
					pac_pos.i=i;
					pac_pos.j=j;
					pac_initial_pos.i=i;
					pac_initial_pos.j=j;
					draw_pacman(i,j,MAP_X,MAP_Y,0);
					break;
				case 'r':
					tel_r.i=i;
					tel_r.j=j;
					break;
				case 'l':
					tel_l.i=i;
					tel_l.j=j;
					break;
				case 'g':
					ghost_pos.i=i;
					ghost_pos.j=j;
					ghost_initial_pos.i=i;
					ghost_initial_pos.j=j;
					break;
				default:
					break;
			}
		}
	}
}

/**
 * Changes the direction of Pac-Man based on the current direction.
 */
void game_changedirection(){
	int new_pos_i,new_pos_j;
	if(current_pill==0){
		game_victory();
	}
	switch(current_direction){
		case RIGHT:
			if(map[pac_pos.i][pac_pos.j]=='r'){
				new_pos_i=tel_l.i;
				new_pos_j=tel_l.j;
			}else{
				new_pos_i=pac_pos.i;
				new_pos_j=pac_pos.j+1;
			}
			break;
		case UP:
			new_pos_i=pac_pos.i-1;
			new_pos_j=pac_pos.j;
			break;
		case DOWN:
			new_pos_i=pac_pos.i+1;
			new_pos_j=pac_pos.j;
			break;
		case LEFT:
			if(map[pac_pos.i][pac_pos.j]=='l'){
				new_pos_i=tel_r.i;
				new_pos_j=tel_r.j;
			}else{
				new_pos_i=pac_pos.i;
				new_pos_j=pac_pos.j-1;
			}
			break;
		default:
			return;
			break;
		}
	if(map[new_pos_i][new_pos_j]=='#'){
		if(old_direction!=current_direction){
			draw_square(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,CELL_SIZE,SECONDARY_COLOR);
			draw_pacman(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,current_direction);
			old_direction=current_direction;
		}
		return;
	}
	if(map[new_pos_i][new_pos_j]=='.'){
		current_pill--;
		current_score+=NP_SCORE;
		tmp_score+=NP_SCORE;
		map[new_pos_i][new_pos_j]=' ';
	}else if(map[new_pos_i][new_pos_j]=='*'){
		current_pill--;
		current_score+=PP_SCORE;
		tmp_score+=PP_SCORE;
		map[new_pos_i][new_pos_j]=' ';
		ghost_status=FRIGHTENED;
		ghost_frightened_countdown=10;
	}
	if( tmp_score>=LIFE_POINT && current_life<3){
		current_life++;
		tmp_score-=LIFE_POINT;
		draw_life(MAP_X,310,current_life);
	}
	draw_score(50,0,TEXT_COLOR,SECONDARY_COLOR,current_score);
	draw_square(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,CELL_SIZE,SECONDARY_COLOR);
	pac_pos.i=new_pos_i;
	pac_pos.j=new_pos_j;
	draw_pacman(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,current_direction);
	return;
}

/**
 * Pauses or resumes the game.
 */
void game_pause(){
	if(game_status){
		disable_timer(0);
		disable_timer(1);
		game_status=0;
		GUI_Text(103+MAP_X,136+MAP_Y, (uint8_t *)PAUSE_TEXT, Yellow, SECONDARY_COLOR);
	}else{
		enable_timer(0);
		enable_timer(1);
		game_status=1;
		draw_scgotext(0,0,TEXT_COLOR,SECONDARY_COLOR);
		draw_score(50,0,TEXT_COLOR, SECONDARY_COLOR,1);
		draw_timer(210,0,TEXT_COLOR, SECONDARY_COLOR,60);
		LCD_FillRect(103+MAP_X,  136+MAP_Y,  103+MAP_X+50,  136+MAP_Y+11, Black);
	}
}

/**
 * Ends the game and displays the game over message.
 */
void game_over(){
	disable_timer(0);
	disable_timer(1);
	disable_RIT();
	GUI_Text(86+MAP_X,136+MAP_Y, (uint8_t *)GOVER_TEXT, Red, SECONDARY_COLOR);
}

/**
 * Ends the game and displays the victory message.
 */
static void game_victory(){
	disable_timer(0);
	disable_timer(1);
	disable_RIT();
	GUI_Text(90+MAP_X,136+MAP_Y, (uint8_t *)GVICTORY_TEXT, Yellow, SECONDARY_COLOR);
}

/**
 * Updates the game timer and handles power pill spawning.
 */
void game_timeupdate(){
	interrupt_per_second--;
	if(interrupt_per_second<=0){
		if(ghost_frightened_countdown!=0 && ghost_status==FRIGHTENED){
			ghost_frightened_countdown--;
		}
		if(ghost_start_time>0){
			ghost_start_time--;
		}
		if(countdown==0){
			game_over();
			return;
		}
		countdown--;
		game_sendinfo();
		draw_timer(210,0,TEXT_COLOR,SECONDARY_COLOR,countdown);
		if(h<RANDOM_PILLS & countdown==randompillspawn[h] ){
			if(map[randompillpos[h].i][randompillpos[h].j]==' '){
				current_pill++;
			}
			map[randompillpos[h].i][randompillpos[h].j]='*';
			draw_circle(randompillpos[h].i,randompillpos[h].j,MAP_X,MAP_Y,2,CELL_SIZE,PP_COLOR);
			h++;
			if(randompillspawn[h]==randompillspawn[h-1]){
				randompillspawn[h]--;
			}			
		}
		interrupt_per_second=5;
	}
	
}

/**
 * Updates the ghost's position and behavior.
 */
void game_ghostupdate(){
	if(ghost_start_time<=0){
		draw_square(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,CELL_SIZE,SECONDARY_COLOR);
		if(map[ghost_pos.i][ghost_pos.j]=='*'){
			draw_circle(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,2,CELL_SIZE,PP_COLOR);
		}else if(map[ghost_pos.i][ghost_pos.j]=='.'){
			draw_circle(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,1,CELL_SIZE,NP_COLOR);
		}

		if(ghost_status==CHASE){
			if(60-countdown>=GHOST_SPEED_CHANGE_TIME){
				init_timer(0, 0, 0, 3, sec_to_count(0.15));
			}
			aggiornaPercorsoFantasma(&ghost_pos,pac_pos);
			draw_ghost(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,GHOST_CHASE_COLOR);
		}else if(ghost_status==FRIGHTENED){
			if(ghost_frightened_countdown>0){
				init_timer(0, 0, 0, 3, sec_to_count(0.3));
				aggiornaPercorsoFantasma(&ghost_pos,trovaPosizioneLontanaDaPacman(pac_pos));
				draw_ghost(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,GHOST_FRIGHTENED_COLOR);
			}else{
				ghost_frightened_countdown=10;
				ghost_status=CHASE;
				init_timer(0, 0, 0, 3, sec_to_count(0.2));
				draw_ghost(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,GHOST_CHASE_COLOR);
			}
		}
	}
}

/**
 * Sends game information via CAN bus.
 */
static void game_sendinfo(){
	CAN_TxMsg.data[3] = (current_score & 0xFF00)>>8;
	CAN_TxMsg.data[2] = (current_score & 0xFF);
	CAN_TxMsg.data[1] = (current_life & 0xFF);
	CAN_TxMsg.data[0] = countdown;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 2;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);   
}

/**
 * Checks the position of Pac-Man and the ghost to handle collisions.
 */
int game_checkpos(){
	if(ghost_pos.i==pac_pos.i && ghost_pos.j==pac_pos.j){
		if(ghost_status==CHASE){
			current_direction=START;
			draw_square(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,CELL_SIZE,SECONDARY_COLOR);
			current_life--;
			draw_life(MAP_X,310,current_life);
			if(current_life<=0){
				game_over();
				return 1;
			}else{
				pac_pos.i=pac_initial_pos.i;
				pac_pos.j=pac_initial_pos.j;
				draw_pacman(pac_pos.i,pac_pos.j,MAP_X,MAP_Y,0);
			}
		}else{
			current_score+=100;
			ghost_status=CHASE;
		}
		ghost_start_time=GHOST_START_DELAY;
		ghost_pos.i=ghost_initial_pos.i;
		ghost_pos.j=ghost_initial_pos.j;
		draw_ghost(ghost_pos.i,ghost_pos.j,MAP_X,MAP_Y,GHOST_CHASE_COLOR);
	}
	return 0;
}

/**
 * Finds a position far from Pac-Man for the ghost to move to when frightened.
 */
static map_pos trovaPosizioneLontanaDaPacman(map_pos pacManPos) {
	int maxDistance = -1;
	volatile map_pos plontana = { -1, -1 };
	int i = 0, j = 0;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (map[i][j] != '#' && aisValid(i, j)) {
				int distance = abs(i - pacManPos.i) + abs(j - pacManPos.j);
				if (distance > maxDistance) {
					maxDistance = distance;
					plontana.i = i;
					plontana.j = j;
				}
			}
		}
	}
	return plontana;
}
