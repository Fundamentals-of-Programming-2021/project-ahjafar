#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WIDTH 800
#define HEIGHT 600

#define IMAGE_SIZE 100

SDL_Window* init();

void draw_map(SDL_Window* window);

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);


#endif