#include "graphic.h"



void player_setup(char name[10],char n_bots){
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
}

int main(int argc, char* argv[]){
    player_setup("AmirHasan",N_BOTS);
    init();
    random_map(N_TERRITORIES);
    draw_map();
    kill();
    return 0;
}