#include <stdio.h>
#include <stdlib.h>
#include "graphic.h"


int main(int argc, char* argv[]){
    SDL_Window* window=init();
    draw_map(window);
    return 0;
}