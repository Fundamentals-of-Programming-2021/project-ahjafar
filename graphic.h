#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "logic.h"

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WIDTH 600
#define HEIGHT 400

#define IMAGE_SIZE 100
#define MENU_WIDTH 300
#define MENU_HEIGHT 350

#define FPS 30

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture *texture, *text;
static TTF_Font* font; 

static SDL_Texture * image_texture;
static SDL_Rect texture_destination;
//SDL_Rect textbox;
static SDL_Surface* textsurface=NULL;
static SDL_Texture* ttfTexture;



void init();

int draw_map(struct territory territory_list[10]);

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

void kill();

int menu();


#endif