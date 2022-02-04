#include "graphic.h"

SDL_Window* init(){
    SDL_Init(SDL_INIT_VIDEO);

    // Create a SDL window
    SDL_Window* window = SDL_CreateWindow("State.io",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH,
                                          HEIGHT,
                                          SDL_WINDOW_OPENGL);
}

void draw_map(SDL_Window* window){
    SDL_Renderer *renderer = SDL_CreateRenderer(window,
                                                -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initialize support for loading PNG and JPEG images
    IMG_Init(IMG_INIT_PNG);

    SDL_Texture * image_texture = initialize_texture_from_file("territories\\1-5.png", renderer);

    // Define where on the "screen" we want to draw the texture
    SDL_Rect texture_destination;
    texture_destination.x = 100;
    texture_destination.y = 50;
    texture_destination.w = IMAGE_SIZE;
    texture_destination.h = IMAGE_SIZE;

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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // Clear screen
        SDL_RenderClear(renderer);
        // Draw
        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);

        filledCircleColor(renderer, 150, 100, 10,  0xff70295d);

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
