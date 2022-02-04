#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WIDTH 800
#define HEIGHT 600

#define IMAGE_SIZE 100

#define N_BOTS 3

#define FPS 30

static const Uint32 colors[6]={0xff1c1a17,0xff0000ff,0xff00ff00,0xffff0000,0xff00ffff,0xff70295d};
static const Uint32 text_colors[6]={0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff};

struct player{
    char* name;
    char id;
    int score;
};

struct territory{
    char id;
    struct player* Player;
};

SDL_Window* init();

void draw_map(SDL_Window* window);

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);


#endif