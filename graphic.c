#include "graphic.h"
#include "logic.h"

void move_soldiers(){
    struct moving* iterator=head,*last=NULL;
    while(iterator!=NULL){
        filledCircleColor(renderer, iterator->x+50, iterator->y+50, 3,  colors[iterator->player_id]);
        iterator->x+=iterator->v_x;
        iterator->y+=iterator->v_y;
        if(abs(iterator->end->x-iterator->x)<10 && abs(iterator->end->y-iterator->y)<10){
            if(iterator->player_id==iterator->end->player_id){
                iterator->end->residents+=iterator->all;
            }else{
                if(iterator->end->residents>iterator->all){
                    iterator->end->residents-=iterator->all;
                }else if(iterator->end->residents+iterator->end->going>iterator->all){
                    iterator->all-=iterator->end->residents;
                    iterator->end->going-=iterator->all;
                }else{
                    iterator->end->player_id=iterator->player_id;
                    iterator->end->residents=iterator->all-(iterator->end->residents+iterator->end->going);
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
}

void show_text(char* text,int x,int y,SDL_Color text_color){
    SDL_Rect textbox = {x, y, 20, 20};
    TTF_SizeText(font, text,&textbox.w, &textbox.h);
    if(textsurface!=NULL){

    }
    textsurface = TTF_RenderText_Blended(font,text,text_color);
    ttfTexture = SDL_CreateTextureFromSurface(renderer, textsurface);
    SDL_RenderCopy(renderer, ttfTexture, NULL, &textbox);
            SDL_DestroyTexture(ttfTexture);
        SDL_FreeSurface(textsurface);
}

int menu(){
    int return_val=0;
    image_texture= initialize_texture_from_file("menu.png", renderer);

    char username[NAME_LENGTH]={0};
    SDL_StartTextInput();

    SDL_Rect textbox = {175, 50, 72, 14},inputbox = {175, 90, 72, 14},start_button={287,318,27,14},
                        continue_button={248,243,103,14},scoreboard_button={270,168,59,14};

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
                    return_val=3;
                    running=0;
                }
            }else if(event.type == SDL_TEXTINPUT){
                //Not copy or pasting
                if(!( SDL_GetModState() & KMOD_CTRL && (event.text.text[0] == 'c' || event.text.text[0] == 'C' || event.text.text[0] == 'v' || event.text.text[0] == 'V' ))){                     //Append character
                    strcpy(username,strcat(username,event.text.text));
                }
            }else if(event.type==SDL_MOUSEBUTTONDOWN){
                if(event.button.x>250 && event.button.x<350 && event.button.button==SDL_BUTTON_LEFT){
                    if(event.button.y>150 && event.button.y<200){
                        //scorboard
                        return_val=1;
                        running=0;
                    }else if(event.button.y>225 && event.button.y<275){
                        //play saved game
                        return_val=2;
                        running=0;
                    }else if(event.button.y>300 && event.button.y<350){
                        //start a new one
                        return_val=3;
                        running=0;
                    }
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_Color text_color = {0, 0, 0, 255};


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
    itoa(state.going+state.residents,residents,10);
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

int draw_map(struct territory territory_list[10]){
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
                    start_point=find_clicked(event.button.x,event.button.y);
                }
            }else if(event.type==SDL_MOUSEBUTTONUP){
                if(event.button.button==SDL_BUTTON_LEFT){
                    end_point=find_clicked(event.button.x,event.button.y);
                    //printf("moved from %d to %d\n",start_point,end_point);
                    if(start_point!=-1 && end_point!=-1 && start_point!=end_point){
                        territory_list[start_point-1].going_list[end_point-1]=territory_list[start_point-1].residents;
                        territory_list[start_point-1].going+=territory_list[start_point-1].residents;
                        territory_list[start_point-1].residents=0;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Clear screen
        SDL_RenderClear(renderer);

        for(int i=0;i<N_TERRITORIES;i++){
            if(territory_list[i].residents<50 && territory_list[i].player_id!=0)
                territory_list[i].residents+=RATE;
        }

        for(int i=0;i<N_TERRITORIES;i++){
            draw_territory(territory_list[i]);
        }

        if(SDL_GetTicks()-t>200){
            territory_list=move();
            t=SDL_GetTicks();
        }

        move_soldiers();

        game_ended(&game_state);

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