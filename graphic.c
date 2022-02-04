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

void random_map(n_territories){
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
    }
}

void draw_territory(struct territory state){
    blah blah blah
}

void draw_map(){
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    IMG_Init(IMG_INIT_PNG);

    TTF_Init();
    font = TTF_OpenFont("LiberationSerif-Bold.ttf", 12);

    SDL_Texture * image_texture = initialize_texture_from_file("territories\\1-5.png", renderer);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;
    texture_destination.x = 100;
    texture_destination.y = 50;
    texture_destination.w = IMAGE_SIZE;
    texture_destination.h = IMAGE_SIZE;

    int w,h;
    TTF_SizeText(font, "5", &w, &h);
    printf("%d %d",w,h);
    SDL_Rect textbox;
    textbox.x = 141;
    textbox.y = 93;
    textbox.w = w;
    textbox.h = h;
    SDL_Color color= {255,255,255,255};
    SDL_Surface* textsurface = TTF_RenderText_Solid(font, "5",color);
    SDL_Texture* ttfTexture = SDL_CreateTextureFromSurface(renderer, textsurface);

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
        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        filledCircleColor(renderer, 150, 100, 10,  0xff70295d);

        SDL_RenderCopy(renderer, ttfTexture, NULL, &textbox);

        // Show what was drawn
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / FPS);
    }

    SDL_DestroyTexture(image_texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    
}

SDL_Texture *initialize_texture_from_file(const char* file_name, SDL_Renderer *renderer) {
    SDL_Surface *image = IMG_Load(file_name);
    SDL_Texture * image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    return image_texture;
}

void kill() {
    
	TTF_CloseFont( font );
	SDL_DestroyTexture( texture );
	texture = NULL;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}