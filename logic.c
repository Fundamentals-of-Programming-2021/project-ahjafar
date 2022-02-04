#include "graphic.h"

#define N_BOTS 3

struct player* player_setup(char name[10],char n_bots){
    struct player* player_list=malloc(sizeof(struct player)*(n_bots+2));
    player_list[0].id=0;
    strcpy(player_list[0].name,"neutral");
    player_list[0].score=0;
    player_list[1].id=1;
    strcpy(player_list[1].name,name);
    player_list[1].score=0;
    char bot_name[25];
    for(int i=2;i<2+n_bots;i++){
        player_list[i].id=i;
        sprintf(bot_name,"BOT%d",i-1);
        strcpy(player_list[i].name,bot_name);
        player_list[i].score=0;
    }
    return player_list;
}

int main(int argc, char* argv[]){
    struct player* player_list=player_setup("AmirHasan",N_BOTS);
    SDL_Window* window=init();
    draw_map(window);
    return 0;
}