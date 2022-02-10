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
#define SCOREBOARD_WIDTH 557
#define SCOREBOARD_HEIGHT 523
#define POTION_WIDTH 20
#define POTION_HEIGHT 27

#define SPEED 2.5

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

struct moving{
    float x;
    float y;
    int all;
    struct territory* start;
    struct territory* end;
    float v_x,v_y;
    int player_id;
    struct moving* next;
    int potion_type;
};

static struct moving* head=NULL;

void init();

int draw_map(struct territory territory_list[10]);

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer);

void kill();

int menu(char username[NAME_LENGTH]);

void show_text(char* text,int x,int y,SDL_Color text_color);

void show_win_lose(char state);

void add_to_moving(struct territory* start,struct territory* end,int n);

void move_soldiers();

void show_scoreboard();

#endif