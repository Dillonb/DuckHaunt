#include "game.h"

Game::Game(int w, int h) {
    this->width = w;
    this->height = h;
    this->radarSize = w / 7;


    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    printf("Created Window\n");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    printf("Created Renderer\n");

    this->surface = SDL_GetWindowSurface(this->window);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface);

    this->world.addDuck(Duck(Radian(0), 20));
    this->world.addDuck(Duck(Radian(0), 30));
    this->world.addDuck(Duck(Radian(0), 0));
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
    printf("Draw Webcam (later)\n");
    //SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00));
    boxRGBA(this->renderer, 0, 0, this->width, this->height, 0x00, 0x00, 0x00, 0xFF);
    printf("box RGBA made\n");
    
=======
    //SDL_FillRect(this->surface, NULL, SDL_MapRGB(this->surface->format, 0x00, 0x00, 0x00));
    boxRGBA(this->renderer, 0, 0, this->width, this->height, 0x00, 0x00, 0x00, 0xFF);

>>>>>>> 7dd0a6c136e37eadbcbe697c1fc2b2f952b4f8e2
    drawRadar();
    printf("Radar Drawn\n");

    SDL_UpdateWindowSurface(this->window);
    printf("Updated Surface\n");

    SDL_RenderPresent(this->renderer);
}

void Game::drawRadar() {
    int radarOriginX = this->width - this->radarSize;
    int radarOriginY = 0;

    // Draw the radar border
    circleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), 45, 0xFF, 0xFF, 0xFF, 0xFF);
    // Draw the dot for the player at the center
    filledCircleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), 2, 0xFF, 0xFF, 0xFF, 0xFF);



    // Draw ducks

    for (list<Duck>::iterator i = this->world.getDuckIterator(); i != this->world.getDuckEnd(); i++) {
        printf("%f\n", i->getDistance());
        // x1 = 32 + x0
        // y1 = 32 - y1
        double duckX = (radarSize / 2) + i->getDistance() * cos((i->getAngle() + this->world.getPlayer().angle).toRad());
        double duckY = (radarSize / 2) - i->getDistance() * sin((i->getAngle() + this->world.getPlayer().angle).toRad());
        printf("At %f rad, %f distance: (%f, %f)\n", i->getAngle().toRad(), i->getDistance(), duckX, duckY);
        filledCircleRGBA(this->renderer,
                radarOriginX + (32 + i->getDistance() * cos(i->getAngle().toRad())),
                radarOriginY + (32 - i->getDistance() * sin(i->getAngle().toRad())),
                2,
                0xFF, 0x00, 0x00,
                0xFF);
    }




}

void Game::drawDucks() {
    
    // Draw ducks
    // iDuck is both the iterator and a pointer to a duck in the list
    // this loops through every duck in the duck list
    for (list<Duck>::iterator iDuck = this->world.getDuckIterator(); iDuck != this->world.getDuckEnd(); iDuck++) {
        
        
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
