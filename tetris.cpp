#include "SDL.h"
#include <stdio.h>
#include <utility>
#include <vector>


using TCoordinate = std::pair <int, int>; //Les coordonnées de chaque carré, x et y/
using TShape = std::vector<TCoordinate>; //Chaque forme est représentée par un vecteur de carrés



int main(int argc, char* argv[]) {

    SDL_Window *window;                    // Declare a pointer
    SDL_Renderer* renderer;
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        640,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    /* We must call SDL_CreateRenderer in order for draw calls to affect this window. */
    renderer = SDL_CreateRenderer(window, -1, 0);

    /* Select the color for drawing. It is set to red here. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    /* Clear the entire screen to our selected color. */
    SDL_RenderClear(renderer);


    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // the rect color (solid red)
    // SDL_Rect rect = {0, 0, 100, 50}; // the rectangle
    // SDL_RenderFillRect(renderer, &rect);
    // SDL_RenderPresent(renderer); // copy to screen


    TShape shape ;
    shape.push_back(std::make_pair(200,50));
    SDL_Rect rect = {shape[0].first, shape[0].second, 100, 100};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer); // copy to screen



    /* Up until now everything was drawn behind the scenes.
       This will show the new, red contents of the window. */
    SDL_RenderPresent(renderer);
    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example



    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
