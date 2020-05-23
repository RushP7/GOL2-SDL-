#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "config.h"
#include "logic.h"

int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	
	SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", 100, 100, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);

	if (!window) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
	}
	
	config_t config = {
		.map = {0},
		.gameState = STATE_SETUP
	};

	SDL_Event event;
	int quit = 0;
	
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_QUIT) {
				quit = 1;
			}

			else if (event.type == SDL_KEYDOWN || config.gameState == STATE_RUN) {
				
				if (event.key.keysym.scancode == SDL_SCANCODE_RETURN)
					config.gameState = STATE_RUN;
				
				nextFrame(&config);
				SDL_Delay(1000 / GAME_SPEED);

			}

			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				remap(&config, event.button.x / CELL_WIDTH, event.button.y / CELL_HEIGHT);
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			renderGame(renderer, &config);
			SDL_RenderPresent(renderer);
			
		}

	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
