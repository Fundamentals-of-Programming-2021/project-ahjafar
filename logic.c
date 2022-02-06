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

void random_map(int n_territories){
    int x,y;
    srand(time(0));
    for(int i=0;i<n_territories;i++){
        char found=0;
        while(!found){
            x=rand()%(WIDTH-IMAGE_SIZE);
            y=rand()%(HEIGHT-IMAGE_SIZE);
            found=1;
            for(int j=0;j<i;j++){
                if(abs(territory_list[j].x-x)<100 && abs(territory_list[j].y-y)<100){
                    found=0;
                    break;
                }
            }
        }
        territory_list[i].x=x;
        territory_list[i].y=y;
        territory_list[i].going=0;
        territory_list[i].player_id=0;
        territory_list[i].residents=STARTERS;
        territory_list[i].id=i+1;
    }
    int p;
    for(int i=1;i<N_BOTS+2;i++){
        char found=0;
        while(!found){
            p=rand()%(N_TERRITORIES);
            found=1;
            if(territory_list[p].player_id!=0){
                found=0;
            }
        }
        territory_list[p].player_id=i;
    }
}

int main(int argc, char* argv[]){
    player_setup("AmirHasan",N_BOTS);
    init();
    int menu_res=menu();
    if(menu_res==3){
        random_map(N_TERRITORIES);
        draw_map(territory_list);
    }
    kill();
    return 0;
}