#ifndef CONFIG_H
#define CONFIG_H

#define SCR_WIDTH 900
#define SCR_HEIGHT 900
#define CELLS 45
#define CELL_WIDTH (SCR_WIDTH / CELLS)
#define CELL_HEIGHT (SCR_HEIGHT / CELLS)
//in frames per second
#define GAME_SPEED 10	

//for gameState
#define STATE_SETUP 0
#define STATE_RUN 1 

//for map state
#define DEAD 0
#define ALIVE 1




typedef struct {
	
	//will be used for GOL's primary algorithm
	int map[(CELLS + 2)][ (CELLS + 2)];	
	int nextMap[(CELLS + 2)][(CELLS + 2)];
	
	int gameState;

}config_t;

#endif 
