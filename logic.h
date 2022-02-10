#ifndef __LOGIC_H__
#define __LOGIC_H__
#define N_BOTS 4
#define N_TERRITORIES 10

#define STARTERS 25
#define NEUTRAL_STARTERS 40 
#define RATE 0.1
#define NAME_LENGTH 40


static const Uint32 colors[6]={0xff1c1a17,0xff0000ff,0xff00ff00,0xffff0000,0xff00ffff,0xff70295d};
static const SDL_Color text_colors[6]={{255,255,255,255},{255,255,255,255},{0,0,0,255},
                                       {255,255,255,255},{0,0,0,255},{255,255,255,255}};

struct player{
    char name[NAME_LENGTH];
    char id;
    int score;
    int potion_type;
};

static struct player player_list[6];

struct potion{
    int x;
    int y;
    int type;
    //1:more producing speed
    //2:no limit
    //3:more moving speed
    //4:freeze
    int player_id;
    int exists;
    double timer;
};

static struct potion potion_list[5];

struct territory{
    char id;
    int player_id;
    float residents;
    int going;
    int going_list[10];
    int x;
    int y;
};


static struct territory territory_list[10];

void game_ended(char* game_state);

void player_setup(char name[10],char n_bots);

void random_map(int n_territories,time_t seed);

int find_clicked(int x,int y);

struct territory* move();

struct territory* AI();

struct territory* AI_V2();

#endif