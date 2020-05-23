#ifndef LOGIC_H_
#define LOGIC_H_

void remap(config_t* config, int row, int column);
void nextFrame(config_t* config);

void renderGame(SDL_Renderer* renderer, const config_t* config);


#endif