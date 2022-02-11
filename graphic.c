#include "graphic.h"
#include "logic.h"

void savemap(int seed){
    FILE* fp=fopen("map.dat","wb");
    char str[20];
    sprintf(str,"%d",seed);
    fwrite(str,20,1,fp);
    fclose(fp);
}

int loadmap(){
    FILE* fp=fopen("map.dat","rb");
    char buf[20];
    fread(buf,20,1,fp);
    fclose(fp);
    return atoi(buf);
}

void potion_timer(struct potion* potion_list,struct player player_list[6]){
    for(int i=0;i<5;i++){
        if(potion_list[i].exists==0)continue;
        potion_list[i].timer-=0.01;
        if(potion_list[i].timer<=0){
            potion_list[i].exists=0;
            if(potion_list[i].player_id!=-1){
                player_list[potion_list[i].player_id-1].potion_type=0;
                switch(potion_list[i].type){
                    case 1:
                        player_list[potion_list[i].player_id-1].rate=1;
                        break;
                    case 2:
                        player_list[potion_list[i].player_id-1].nolimit=0;
                        break;
                    case 3:
                        player_list[potion_list[i].player_id-1].speed=1;
                        break;
                    case 4:
                        is_moving=0;
                        break;
                }
            }
        }
    }
}

void get_potions(int x,int y,int player_id,struct player player_list[6]){
    for(int i=0;i<5;i++){
        if(potion_list[i].exists==0)continue;
        if(abs(potion_list[i].x+10-x)<15 && abs(potion_list[i].y+10-y)<15 && player_list[player_id-1].potion_type==0 && potion_list[i].player_id==-1){
            potion_list[i].player_id=player_id;
            potion_list[i].timer=10.00;
            player_list[player_id-1].potion_type=potion_list[i].type;
            switch(potion_list[i].type){
                case 1:
                    player_list[player_id-1].rate=3;
                    break;
                case 2:
                    player_list[player_id-1].nolimit=1;
                    break;
                case 3:
                    player_list[potion_list[i].player_id-1].speed=2;
                    break;
                case 4:
                    is_moving=potion_list[i].player_id;
                    potion_list[i].timer=2.00;
                    break;
            }
        }
    }
}

void draw_potions(struct territory* territory_list,struct potion* potion_list){
    for(int i=0;i<5;i++){
        char image_addr[25];
        if(potion_list[i].exists==1 && potion_list[i].player_id==-1){
            sprintf(image_addr,"potions\\%d.png",potion_list[i].type);
            SDL_Texture * image_texture2= initialize_texture_from_file(image_addr, renderer);

            texture_destination.x = potion_list[i].x;
            texture_destination.y = potion_list[i].y;
            texture_destination.w = POTION_WIDTH;
            texture_destination.h = POTION_HEIGHT;

            SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
        }else if (potion_list[i].exists==1){
            sprintf(image_addr,"potions\\%d.png",potion_list[i].type);
            SDL_Texture * image_texture2= initialize_texture_from_file(image_addr, renderer);
            texture_destination.x = 10;
            texture_destination.y = potion_list[i].player_id*15;
            texture_destination.w = POTION_WIDTH/2;
            texture_destination.h = POTION_HEIGHT/2;

            SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
            boxColor(renderer,
                    20,
                    potion_list[i].player_id*15+5,
                    20+potion_list[i].timer*5,
                    potion_list[i].player_id*15+10,
                    colors[potion_list[i].player_id]);
        }
        SDL_DestroyTexture(image_texture);
    }
}

void show_text(char* text,int x,int y,SDL_Color text_color){
    SDL_Rect textbox = {x, y, 20, 20};
    TTF_SizeText(font, text,&textbox.w, &textbox.h);
    textsurface = TTF_RenderText_Blended(font,text,text_color);
    ttfTexture = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_RenderCopy(renderer, ttfTexture, NULL, &textbox);
    SDL_DestroyTexture(ttfTexture);
    SDL_FreeSurface(textsurface);
}

void push(int scores[5],char users[5][NAME_LENGTH],int score,char user[NAME_LENGTH],int n,int all){
    for(int i=all;i>=n;i--){
        strcpy(users[i],users[i-1]);
        scores[i]=scores[i-1];
    }
    strcpy(users[n],user);
    scores[n]=score;
}

int map_setting(){
    SDL_Texture * image_texture= initialize_texture_from_file("menu.png", renderer);
    
    SDL_Event event;
    while(1){        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                return 0;
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(event.button.x>235 && event.button.x<365 && event.button.button==SDL_BUTTON_LEFT){
                    if(event.button.y>40 && event.button.y<90){
                        return 1;
                    }else if(event.button.y>105 && event.button.y<155){
                        return 2;
                    }else if(event.button.y>170 && event.button.y<220){
                        return 3;
                    }else if(event.button.y>235 && event.button.y<285){
                        return loadmap(); 
                    }else if(event.button.y>300 && event.button.y<350){
                        return time(0); 
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        texture_destination.x = 150;
        texture_destination.y = 15;
        texture_destination.w = MENU_WIDTH;
        texture_destination.h = MENU_HEIGHT;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        boxColor(renderer, 235, 40, 365, 90, 0x44ff0000);
        boxColor(renderer, 235, 105, 365, 155, 0x44ff0000);
        boxColor(renderer, 235, 170, 365, 220, 0x44ff0000);
        boxColor(renderer, 235, 235, 365, 285, 0x44ff0000);
        boxColor(renderer, 235, 300, 365, 350, 0x44ff0000);

        show_text("Map 1",283,58,text_color);
        show_text("Map 2",283,123,text_color);
        show_text("Map 3",283,188,text_color);
        show_text("Load Map",275,253,text_color);
        show_text("Random map",267, 318,text_color);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(image_texture);
}

void show_scoreboard(){
    FILE* fp=fopen("users.txt","r");
    int scores[5],score,all=0,added=0;
    char users[5][NAME_LENGTH];
    char* user;
    char line[NAME_LENGTH+50];
    while(fgets(line, NAME_LENGTH+50, fp)) {
        user=strtok(line," ");
        score=atoi(strtok(NULL," "));
        for(int i=0;i<=all;i++){
            if(scores[i]<score){
                push(scores,users,score,user,i,all);
                if(all<4)all++;
                added=1;
                break;
            }
        }
        if(all<4 && added==0){
            push(scores,users,score,user,0,all);
            all++;
            added=1;
        }
    }
    if(all==4)all++;
    SDL_Texture * image_texture2= initialize_texture_from_file("scoreboard.png", renderer);
    
    char running = 1;
    SDL_Event event;
    while(running){        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }else if(event.type == SDL_KEYDOWN){
                //Handle backspace
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    //lop off character
                    running = 0;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        texture_destination.x = 150;
        texture_destination.y = 15;
        texture_destination.w = MENU_WIDTH;
        texture_destination.h = MENU_HEIGHT;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, image_texture2, NULL, &texture_destination);

        for (int i=0; i<all; i++){
            show_text(users[i],260,95+57*i,text_color);
            char* s=malloc(sizeof(char)*10);
            sprintf(s,"%d",scores[i]);
            show_text(s,380,95+57*i,text_color);
        }

        show_text("Press ESC to continue",240,370,text_color);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(image_texture2);
}

void show_win_lose(char state){
    image_texture= initialize_texture_from_file("menu.png", renderer);

    char running = 1;
    SDL_Event event;
    while(running){        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }else if(event.type == SDL_KEYDOWN){
                //Handle backspace
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    //lop off character
                    return;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        texture_destination.x = 150;
        texture_destination.y = 25;
        texture_destination.w = MENU_WIDTH;
        texture_destination.h = MENU_HEIGHT;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        if(state){
            show_text("You win.",270,136,text_color);
            show_text("Score:",275,168,text_color);
            show_text("100",280,200,text_color);
        }else{
            show_text("You lose.",270,136,text_color);
            show_text("Score:",275,168,text_color);
            show_text("-50",278,200,text_color);
        }
        show_text("Press ESC to continue",240,232,text_color);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
}

void delete_moving(struct moving** head){
    struct moving* current = *head;
    struct moving* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
 
    *head = NULL;
}

void move_soldiers(struct player player_list[6]){
    struct moving* iterator=head,*last=NULL;
    while(iterator!=NULL){
        filledCircleColor(renderer, iterator->x+50, iterator->y+50, 3,  colors[iterator->player_id]);
        if(is_moving){
            if(iterator->player_id==is_moving){
                iterator->x+=player_list[iterator->player_id-1].speed*iterator->v_x;
                iterator->y+=player_list[iterator->player_id-1].speed*iterator->v_y;
            }
        }else{
            iterator->x+=player_list[iterator->player_id-1].speed*iterator->v_x;
            iterator->y+=player_list[iterator->player_id-1].speed*iterator->v_y;
        }
        
        if(abs(iterator->end->x-iterator->x)<10 && abs(iterator->end->y-iterator->y)<10){
            if(iterator->player_id==iterator->end->player_id){
                iterator->end->residents+=iterator->all;
            }else{
                if(iterator->end->residents>iterator->all){
                    iterator->end->residents-=iterator->all;
                }else if(iterator->end->residents+iterator->end->going>iterator->all){
                    iterator->all-=iterator->end->residents;
                    iterator->end->going-=iterator->all;
                    for(int i=0;iterator->all!=0;i++){
                        if(iterator->end->going_list[i]>iterator->all){
                            iterator->end->going_list[i]-=iterator->all;
                            iterator->all=0;
                        }else{
                            iterator->all-=iterator->end->going_list[i];
                            iterator->end->going_list[i];
                        }
                    }
                }else{
                    iterator->end->player_id=iterator->player_id;
                    iterator->end->residents=iterator->all-(iterator->end->residents+iterator->end->going);
                    iterator->end->going=0;
                    for(int i=0;i<N_TERRITORIES;i++){
                        iterator->end->going_list[i]=0;
                    }
                }
            }
            if(iterator!=head){
                struct moving* next=iterator->next;
                free(iterator);
                last->next=next;
                iterator=last;
            }else{
                struct moving* next=iterator->next;
                free(head);
                head=next;
                iterator=head;
                continue;
            }
        }
        get_potions(iterator->x+50,iterator->y+50,iterator->player_id,player_list);
        last=iterator;
        iterator=iterator->next;
    }

}

void add_to_moving(struct territory* start,struct territory* end,int n){
    struct moving* moving_ptr=malloc(sizeof(struct moving));
    moving_ptr=malloc(sizeof(struct moving));
    moving_ptr->all=n;
    float distance=sqrt(pow(start->x-end->x,2)+pow(start->y-end->y,2));
    moving_ptr->v_x=(end->x-start->x)/distance*SPEED;
    moving_ptr->v_y=(end->y-start->y)/distance*SPEED;
    moving_ptr->next=NULL;
    moving_ptr->x=start->x;
    moving_ptr->y=start->y;
    moving_ptr->player_id=start->player_id;
    moving_ptr->start=start;
    moving_ptr->end=end;
    if(head==NULL){
        head=moving_ptr;
    }
    else{
        struct moving* iterator=head;
        while(iterator->next!=NULL){
            iterator=iterator->next;
        }
        iterator->next=moving_ptr;
    }

}

void init(){
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    window = SDL_CreateWindow("State.io",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WIDTH,
                               HEIGHT,
                               SDL_WINDOW_OPENGL);
    
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Bold.ttf", 12);
    
    for(int i=0;i<5;i++){
        potion_list[i].exists=0;
    }
}

int menu(char username[NAME_LENGTH]){
    int return_val=0;
    image_texture= initialize_texture_from_file("menu.png", renderer);

    SDL_StartTextInput();

    char running = 1;
    SDL_Event event;
    while(running){        
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = 0;
            }else if(event.type == SDL_KEYDOWN){
                //Handle backspace
                if(event.key.keysym.sym == SDLK_BACKSPACE && strlen(username) > 0){
                    //lop off character
                    username[strlen(username)-1]='\0';
                }else if(event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL){
                    SDL_SetClipboardText(username);
                }else if(event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL){
                    strcpy(username , SDL_GetClipboardText());
                }else if(event.key.keysym.sym == SDLK_RETURN){
                    //start a new one
                    if(strlen(username)==0){
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                        "Username Error",
                        "Please enter username.",
                        window);
                    }else{
                        return_val=3;
                        running=0;
                    }
                }
            }else if(event.type == SDL_TEXTINPUT){
                //Not copy or pasting
                if(!( SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V' ))){                     //Append character
                    strcpy(username,strcat(username,event.text.text));
                }
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(event.button.x>235 && event.button.x<365 && event.button.button==SDL_BUTTON_LEFT){
                    if(event.button.y>150 && event.button.y<200){
                        //scorboard
                        show_scoreboard();
                    }else if(event.button.y>225 && event.button.y<275){
                        //play saved game
                        return_val=2;
                        running=0;
                    }else if(event.button.y>300 && event.button.y<350){
                        //start a new one
                        if(strlen(username)==0){
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                            "Username Error",
                            "Please enter username.",
                            window);
                        }else{
                            return_val=3;
                            running=0;
                        }
                    }
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        texture_destination.x = 150;
        texture_destination.y = 25;
        texture_destination.w = MENU_WIDTH;
        texture_destination.h = MENU_HEIGHT;

        SDL_RenderClear(renderer);


        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        show_text("Player Name:",175, 50,text_color);

        //textbox
        boxColor(renderer, 170, 85, 430, 105, 0xffffffff);
        //buttons
        boxColor(renderer, 235, 150, 365, 200, 0x44ff0000);
        boxColor(renderer, 235, 225, 365, 275, 0x44ff0000);
        boxColor(renderer, 235, 300, 365, 350, 0x44ff0000);

        if(strlen(username)!=0){
            show_text(username,175,90,text_color);
        }else{
            show_text(" ",175,90,text_color);
        }

        show_text("Scoreboard",270,168,text_color);

        show_text("Continue Last Save",248,243,text_color);

        show_text("Start",287, 318,text_color);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);

    }
    SDL_DestroyTexture(image_texture);
    return return_val;
}

void draw_territory(struct territory state){

    char image_addr[25];
    sprintf(image_addr,"territories\\%d-%d.png",state.id,state.player_id);
    image_texture= initialize_texture_from_file(image_addr, renderer);

    // Define where on the "screen" we want to draw the texture
    texture_destination.x = state.x;
    texture_destination.y = state.y;
    texture_destination.w = IMAGE_SIZE;
    texture_destination.h = IMAGE_SIZE;

    char residents[5];
    itoa(state.going+state.residents+0.5,residents,10);
    int offset;
    switch(strlen(residents)){
        case 1:
            offset=6;
            break;
        case 2:
            offset=2;
            break;
        case 3:
            offset=-1;
            break;
        case 4:
            offset=-4;
            break;
    }
    
    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
    filledCircleColor(renderer, state.x+50, state.y+50, 10,  colors[state.player_id]);
    show_text(residents,state.x+43+offset,state.y+43,text_colors[state.player_id]);

    SDL_DestroyTexture(image_texture);
}

void add_potion(struct territory* territory_list,struct potion* potion_list){
    if(rand()%350!=0)return;
    int r1=rand()%10,r2=rand()%10,w1=rand()%50+10,w2=rand()%50+10;
    while(r2==r1)r2=rand()%10;
    int x=(w1*(territory_list[r1].x+50)+w2*(territory_list[r2].x+50))/(w1+w2);
    int y=(w1*(territory_list[r1].y+50)+w2*(territory_list[r2].y+50))/(w1+w2);
    int type=rand()%4+1;
    for(int i=0;i<5;i++){
        if(potion_list[i].exists==1)continue;
        potion_list[i].x=x;
        potion_list[i].y=y;
        potion_list[i].exists=1;
        potion_list[i].timer=10.00;
        potion_list[i].player_id=-1;
        potion_list[i].type=type;
        break;
    }
}

int draw_map(struct territory territory_list[10],struct player player_list[6],int seed){
    char game_state = 1;
    int start_point=-1;
    int end_point=-1;
    SDL_Event event;
    int t=SDL_GetTicks();
    while(game_state==1)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                game_state = 0;
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(event.button.button==SDL_BUTTON_LEFT){
                    if(event.button.x>10 && event.button.x<70 && event.button.y>90 && event.button.y<110){
                        savemap(seed);
                    }else{
                        start_point=find_clicked(event.button.x,event.button.y);
                    }
                }
            }else if(event.type==SDL_MOUSEBUTTONUP){
                if(event.button.button==SDL_BUTTON_LEFT){
                    end_point=find_clicked(event.button.x,event.button.y);
                    if(start_point!=-1 && end_point!=-1 && start_point!=end_point){
                        territory_list[start_point-1].going_list[end_point-1]=territory_list[start_point-1].residents;
                        territory_list[start_point-1].going+=territory_list[start_point-1].residents;
                        territory_list[start_point-1].residents=0;
                    }
                    start_point=-1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Clear screen
        SDL_RenderClear(renderer);

        for(int i=0;i<N_TERRITORIES;i++){
            if(player_list[territory_list[i].player_id-1].nolimit==1)
                territory_list[i].residents+=player_list[territory_list[i].player_id-1].rate*RATE;
            else if(territory_list[i].residents<50 && territory_list[i].player_id!=0)
                territory_list[i].residents+=player_list[territory_list[i].player_id-1].rate*RATE;
        }

        for(int i=0;i<N_TERRITORIES;i++){
            draw_territory(territory_list[i]);
        }

        if(SDL_GetTicks()-t>200){
            territory_list=move(is_moving);
            t=SDL_GetTicks();
        }
        
        add_potion(territory_list,potion_list);

        potion_timer(potion_list,player_list);
        
        boxColor(renderer,10,90,70,110,0x77993311);
        show_text("Save Map",15,91,text_color);

        draw_potions(territory_list,potion_list);

        move_soldiers(player_list);

        game_ended(&game_state);

        //territory_list=AI_V2();

        int mouse_x,mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);
        if(start_point!=-1){
            SDL_RenderDrawLine(renderer,
                               territory_list[start_point-1].x+50,territory_list[start_point-1].y+50,
                               mouse_x,mouse_y);
        }
        // Show what was drawn
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
  return game_state;
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer* renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void kill() {
    
    delete_moving(&head);

	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
    SDL_DestroyTexture(image_texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}