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

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#define WIDTH 600
#define HEIGHT 400

#define IMAGE_SIZE 100

#define NUMBER_WIDTH 18
#define NUMBER_HEIGHT 14

#define FPS 30

#define N_BOTS 3
#define N_TERRITORIES 10

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture *texture, *text;
static TTF_Font* font; 

static const Uint32 colors[6]={0xff1c1a17,0xff0000ff,0xff00ff00,0xffff0000,0xff00ffff,0xff70295d};
static const Uint32 text_colors[6]={0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff};

static SDL_Texture * image_texture;
static SDL_Rect texture_destination;
static SDL_Rect textbox;
static SDL_Surface* textsurface;
static SDL_Texture* ttfTexture;

struct player{
    char name[25];
    char id;
    int score;
};

static struct player player_list[6];

struct territory{
    char id;
    int player_id;
    int residents;
    int going;
    int x;
    int y;
};

static struct territory territory_list[10];

void init();

void draw_map();

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

void random_map(int n_territories);

void kill();

#endif