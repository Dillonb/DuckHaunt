#include "game.h"

Game::Game(int w, int h) {
    this->width = w;
    this->height = h;

    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    this->surface = SDL_GetWindowSurface(this->window);
}

void Game::redraw() {
    // Fill screen with black (eventually draw output of webcam here)
    SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00));


    SDL_UpdateWindowSurface(this->window);
}

void Game::run() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        SDL_Delay(100); // Wait 100ms before trying again when the stack of events becomes empty

        while (SDL_PollEvent(&e) != 0) { // Pull events from the stack until we can't anymore
            // Loop through each type of event
            switch(e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    // A key was pressed, switch for which key
                    switch(e.key.keysym.sym) {
                        case SDLK_ESCAPE: // Esc
                            quit = true; // Quit the game
                            break;
                    }
            }
        }
        this->redraw();
    }
}
