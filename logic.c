#include "graphic.h"
#include "logic.h"

struct territory* AI(){
    if(rand()%100!=0)return territory_list;
    int t1,t2=rand()%N_TERRITORIES,t3=rand()%N_TERRITORIES;
    while(territory_list[(t1=rand()%N_TERRITORIES)].player_id<2 || territory_list[t1].residents<20);
    if(territory_list[t2].residents+territory_list[t2].going>=territory_list[t3].residents+territory_list[t3].going){
        territory_list[t1].going_list[t2]=territory_list[t1].residents;
    }else{
        territory_list[t1].going_list[t3]=territory_list[t1].residents;
    }
    territory_list[t1].going+=territory_list[t1].residents;
    territory_list[t1].residents=0;
    return territory_list;
}

void add_user_score(char username[NAME_LENGTH],int add){
    FILE* fp=fopen("users.txt","r+");
    char line[NAME_LENGTH+50];
    char user[100][NAME_LENGTH];
    int score[100];
    int i=0;
    int new=1;
    while(fgets(line, 100, fp)) {
        strcpy(user[i],strtok(line," "));
        score[i]=atoi(strtok(NULL," "));
        if(strcmp(user[i],username)==0){
            score[i]+=add;
            new=0;
        }
        i++;
    }
    fseek(fp, 0,SEEK_SET);
    for(int j=0;j<i;j++){
        fprintf(fp,"%s %d\n",user[j],score[j]);
    }
    if(new){
        fprintf(fp,"%s %d\n",username,add);
    }
    fflush(fp);
    fclose(fp);
}

void game_ended(char* game_state){
    int player_in_game=0,bots_in_game=0;
    for(int i=0;i<10;i++){
        if(territory_list[i].player_id==1)player_in_game=1;
        else if(territory_list[i].player_id>1)bots_in_game=1;
    }
    if(player_in_game==0){
        *game_state=2;
    }else if(bots_in_game==0){
        *game_state=3;
    }
}

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
        player_list[i].potion_type=0;
    }
}

void random_map(int n_territories,time_t seed){
    int x,y;
    srand(seed);
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
        territory_list[i].residents=NEUTRAL_STARTERS;
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
        territory_list[p].residents=STARTERS;
    }
}

int find_clicked(int x,int y){
    int found=-1;
    for(int i=0;i<10;i++){
        if(x>territory_list[i].x+40 && x<territory_list[i].x+60 &&
           y>territory_list[i].y+40 && y<territory_list[i].y+60){
               found=territory_list[i].id;
               break;
           }
    }
    return found;
}

struct territory* move(){
    for(int i=0;i<N_TERRITORIES;i++){
        for(int j=0;j<N_TERRITORIES;j++){
            if(territory_list[i].going_list[j]>2){
                add_to_moving(&territory_list[i],&territory_list[j],2);
                territory_list[i].going_list[j]-=2;
                territory_list[i].going-=2;
            }else if(territory_list[i].going_list[j]>0){
                add_to_moving(&territory_list[i],&territory_list[j],territory_list[i].going_list[j]);
                territory_list[i].going-=territory_list[i].going_list[j];
                territory_list[i].going_list[j]=0;
            }
        }
    }
    return territory_list;
}

int main(int argc, char* argv[]){
    char username[NAME_LENGTH]={0};
    init();
    int menu_res=menu(username),game_res=0;
    if(menu_res==3){
        player_setup(username,N_BOTS);
        random_map(N_TERRITORIES,time(0));
        game_res=draw_map(territory_list);
    }
    if(game_res==0){
        kill();
        return 0;
    }else if(game_res==2){
        show_win_lose(0);
        add_user_score(username,-50);
        kill();
        main(0,NULL);
    }else if(game_res==3){
        show_win_lose(1);
        add_user_score(username,100);
        kill();
        main(0,NULL);
    }

}