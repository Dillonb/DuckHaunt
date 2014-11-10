#include "game.h"

Game::Game(int w, int h) {
    this->width = w;
    this->height = h;
    this->radarSize = w / 7;


    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->surface = SDL_GetWindowSurface(this->window);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    this->world.addDuck(Duck(Radian(90), 20));
    this->world.addDuck(Duck(Radian(90), 30));
    this->world.addDuck(Duck(Radian(90), 10));
    //this->world.addDuck(Duck(Radian(20), 40));
    printf("Added all ducks\n");

}

// Turns the player left by amount of turnyness
void Game::turnLeft(Radian amount) {
    this->world.getPlayer().turnLeft(amount);
}

// Turns the player right by amount of turnyness
void Game::turnRight(Radian amount) {
    this->world.getPlayer().turnRight(amount);
}

void Game::redraw() {
    // Fill screen with black (eventually draw output of webcam here)
    //SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00));
    boxRGBA(this->renderer, 0, 0, this->width, this->height, 0x00, 0x00, 0x00, 0xFF);

    drawRadar();

    SDL_UpdateWindowSurface(this->window);
    SDL_RenderPresent(this->renderer);
}

void Game::drawRadar() {
    int radarOriginX = this->width - this->radarSize;
    int radarOriginY = 0;

    // Draw the radar border
    circleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), radarSize / 2, 0xFF, 0xFF, 0xFF, 0xFF);

    // Draw the dot for the player at the center
    filledCircleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), 2, 0xFF, 0xFF, 0xFF, 0xFF);

    printf("Drawing player center at (%f, %f)\n", (this->radarSize / 2), (this->radarSize / 2));
    // Draw ducks on the radar

    for (list<Duck>::iterator i = this->world.getDuckIterator(); i != this->world.getDuckEnd(); i++) {
        printf("%f\n", i->getDistance());
        // x1 = 32 + x0
        // y1 = 32 - y1
        double duckX = (radarSize / 2) + i->getDistance() * cos((i->getAngle() + this->world.getPlayer().angle).toRad());
        double duckY = (radarSize / 2) - i->getDistance() * sin((i->getAngle() + this->world.getPlayer().angle).toRad());
        printf("At %f rad, %f distance: (%f, %f)\n", i->getAngle().toRad(), i->getDistance(), duckX, duckY);
        filledCircleRGBA(this->renderer,
                radarOriginX + duckX,
                radarOriginY + duckY,
                2,
                0xFF, 0x00, 0x00,
                0xFF);
    }




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
                        case SDLK_LEFT:
                            printf("Turning left.\n");
                            turnLeft(Radian(10));
                            break;
                        case SDLK_RIGHT:
                            printf("Turning right.\n");
                            turnLeft(Radian(10));
                            break;
                    }
            }
        }
        this->redraw();
    }
}
