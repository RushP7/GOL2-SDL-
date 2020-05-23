#include <SDL.h>
#include "config.h"
#include "logic.h"


//calculates the number of alive neighbors around a cell 
int calcNeighbors(config_t* config, int i, int j) {

	int neighbors = 0;
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++) {
			if (config->map[i + y][j + x] == ALIVE && !(x==0 && y==0))
				neighbors++;
		}
	return neighbors;
}

void remap(config_t* config, int column, int row) {
	config->map[row + 1][column + 1] = ALIVE;
}

//creates the next frame using the conditons for GOL
void nextFrame(config_t* config) {

	for(int i = 1; i <= CELLS; i++)
		for (int j = 1; j <= CELLS; j++) {
			switch (config->map[i][j]) {
				
			case ALIVE:
				if (calcNeighbors(config, i, j) == 2 || calcNeighbors(config, i, j) == 3)
					config->nextMap[i][j] = ALIVE;
				else
					config->nextMap[i][j] = DEAD;
				break;

			case DEAD:
				if (calcNeighbors(config, i, j) == 3)
					config->nextMap[i][j] = ALIVE;
				else
					config->nextMap[i][j] = DEAD;
				break;
			}

		}

	for (int i = 1; i <= CELLS; i++)
		for (int j = 1; j <= CELLS; j++)
			config->map[i][j] = config->nextMap[i][j];
}

void renderGrid(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

	for (int i = 1; i < CELLS; i++) {
		SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCR_HEIGHT);
		SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCR_WIDTH, i * CELL_HEIGHT);
	}
}

void renderCell(SDL_Renderer* renderer, const config_t* config) {

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);

	for (int i = 1; i <= CELLS; i++)
		for (int j = 1; j <= CELLS; j++) {

			if (config->map[i][j] == ALIVE) {
				SDL_Rect rect;
				rect.x = (j - 1) * CELL_WIDTH;
				rect.y = (i - 1) * CELL_HEIGHT;
				rect.w = CELL_WIDTH;
				rect.h = CELL_HEIGHT;

				SDL_RenderFillRect(renderer, &rect);
			}
		}
}


void renderGame(SDL_Renderer* renderer, const config_t* config) {

	if (config->gameState == STATE_SETUP)
		renderGrid(renderer);
	renderCell(renderer, config);

}

