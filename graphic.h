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
#define MENU_WIDTH 300
#define MENU_HEIGHT 350

#define FPS 30

#define N_BOTS 4
#define N_TERRITORIES 10

#define STARTERS 25
#define RATE 0.1
#define NAME_LENGTH 40

static SDL_Window* window;
static SDL_Renderer* renderer;
static SDL_Texture *texture, *text;
static TTF_Font* font; 

static const Uint32 colors[6]={0xff1c1a17,0xff0000ff,0xff00ff00,0xffff0000,0xff00ffff,0xff70295d};
static const SDL_Color text_colors[6]={{255,255,255,255},{255,255,255,255},{0,0,0,255},
                                       {255,255,255,255},{0,0,0,255},{255,255,255,255}};

static SDL_Texture * image_texture;
static SDL_Rect texture_destination;
static SDL_Rect textbox;
static SDL_Surface* textsurface;
static SDL_Texture* ttfTexture;

struct player{
    char name[NAME_LENGTH];
    char id;
    int score;
};

static struct player player_list[6];

struct territory{
    char id;
    int player_id;
    float residents;
    int going;
    int x;
    int y;
};
struct InputWidget{
	int x;
	int y;
	int maxLength;
	char *text;
};

static struct territory territory_list[10];

void init();

void draw_map(struct territory territory_list[10]);

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

void kill();

void menu();

#endif