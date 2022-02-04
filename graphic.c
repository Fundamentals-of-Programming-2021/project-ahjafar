#include "graphic.h"

void init(){
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    window = SDL_CreateWindow("State.io",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WIDTH,
                               HEIGHT,
                               SDL_WINDOW_OPENGL);
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
    int w,h=14,offset;
    switch(strlen(residents)){
        case 1:
            w=6;
            offset=6;
            break;
        case 2:
            w=12;
            offset=2;
            break;
        case 3:
            w=18;
            offset=-1;
            break;
        case 4:
            w=24;
            offset=-4;
            break;
    }
    textbox.x = state.x+43+offset;
    textbox.y = state.y+43;
    textbox.w = w;
    textbox.h = h;
    textsurface = TTF_RenderText_Solid(font, residents,text_colors[state.player_id]);
    ttfTexture = SDL_CreateTextureFromSurface(renderer, textsurface);

    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
    filledCircleColor(renderer, state.x+50, state.y+50, 10,  colors[state.player_id]);
    SDL_RenderCopy(renderer, ttfTexture, NULL, &textbox);
    
    SDL_DestroyTexture(image_texture);
    SDL_DestroyTexture(ttfTexture);
    SDL_FreeSurface(textsurface);
}

void draw_map(){
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Bold.ttf", 12);

    int running = 1;
    SDL_Event event;
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // Clear screen
        SDL_RenderClear(renderer);

        for(int i=0;i<N_TERRITORIES;i++){
            draw_territory(territory_list[i]);
        }

        // Show what was drawn
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }
  
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