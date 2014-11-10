#include "game.h"

Game::Game(int w, int h) {
    this->cap = VideoCapture(0);
    this->width = w;
    this->height = h;
    this->radarSize = w / 7;

    if(!this->cap.isOpened()) return; // check if we succeeded

    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    printf("Created Window\n");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED); // draw things to screen
    printf("Created Renderer\n");

    this->surface = SDL_GetWindowSurface(this->window); // 
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface); // SDL_Texture - A structure that contains an efficient, driver-specific representation of pixel data.

    this->world.addDuck(Duck(Radian(10), 20));
    this->world.addDuck(Duck(Radian(20), 30));
    this->world.addDuck(Duck(Radian(30), 0));
    this->world.addDuck(Duck(Radian(20), 40));
    printf("Added all ducks\n");

}

void Game::redraw() {
    this->cap >> this->image; // get a new frame from camera

    //convert it to SDL_Surface
    SDL_Texture* frame=SDL_CreateTextureFromSurface(this->renderer, convertToSDLSurface(this->image));
    SDL_RenderCopy(this->renderer, frame, NULL, NULL);
    //render the whole thing out to 0,0 coordinate
    // SDL_BlitSurface(frame,NULL,this->surface,NULL);
    //avoid memory leaks
    // SDL_FreeSurface(frame);

    // Fill screen with black (eventually draw output of webcam here)
    printf("Drawing Webcam\n");

    drawDucks();
    printf("Ducks Drawn\n");

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
    circleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), radarSize / 2, 0xFF, 0xFF, 0xFF, 0xFF);
    // Draw the dot for the player at the center
    filledCircleRGBA(this->renderer, radarOriginX + (this->radarSize / 2), radarOriginY + (this->radarSize / 2), 2, 0xFF, 0xFF, 0xFF, 0xFF);



    // Draw ducks on radar

    for (list<Duck>::iterator i = this->world.getDuckIterator(); i != this->world.getDuckEnd(); i++) {
        printf("%f\n", i->getDistance());
        // x1 = 32 + x0
        // y1 = 32 - y1
        double duckX = (radarSize / 2) + i->getDistance() * cos((i->getAngle() + this->world.getPlayer()->angle).toRad());
        double duckY = (radarSize / 2) - i->getDistance() * sin((i->getAngle() + this->world.getPlayer()->angle).toRad());
        printf("At %f rad, %f distance: (%f, %f)\n", i->getAngle().toRad(), i->getDistance(), duckX, duckY);
        filledCircleRGBA(this->renderer,
                radarOriginX + duckX,
                radarOriginY + duckY,
                2,
                0xFF, 0x00, 0x00,
                0xFF);
    }




}

void Game::drawDucks() {
    SDL_Rect duckRect;
    duckRect.x = 288;
    duckRect.y = 208;
    duckRect.w = 64;
    duckRect.h = 64;

    //Draw Ducks every 15 frames
    if (this->frameCount == 0)
    {
        printf("Ducks actually Redrawn\n");
        // Draw ducks
        // iDuck is both the iterator and a pointer to a duck in the list
        // this loops through every duck in the duck list
        for (list<Duck>::iterator iDuck = this->world.getDuckIterator(); iDuck != this->world.getDuckEnd(); iDuck++) {
            typeNum = iDuck->getType();
            //SDL_RenderCopy(renderer,duckTexture[typeNum],NULL, &duckRect);
        }
    } else if (this->frameCount == 14){
        this->frameCount = -1;
    }

    this->frameCount++;
}

void Game::run() {
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        SDL_Delay(10); // Wait 100ms before trying again when the stack of events becomes empty

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
                            this->world.getPlayer()->turnLeft(Radian(10));
                            break;
                        case SDLK_RIGHT:
                            printf("Turning right.\n");
                            this->world.getPlayer()->turnRight(Radian(10));
                            break;
                    }
            }
        }
        this->redraw();
    }
}

SDL_Surface* Game::convertToSDLSurface(const Mat& img){
    //"convert" it to older format, because I found conversation for that, and it's too late for me to rewrite it to the newer Mat
    IplImage opencvimg2=(IplImage)img;
    IplImage* opencvimg=&opencvimg2;
    //do the actual conversation to the good ol' SDL_Surface
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)opencvimg->imageData,
                                                    opencvimg->width,
                                                    opencvimg->height,
                                                    opencvimg->depth*opencvimg->nChannels,
                                                    opencvimg->widthStep,
                                                    0xff0000, 0x00ff00, 0x0000ff, 0);
    return surface;
}
