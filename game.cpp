#include "game.h"

Game::Game(int w, int h) {
    this->cap = VideoCapture(0);
    this->width = w;
    this->height = h;
    this->radarSize = w / 7;

    IMG_Init(IMG_INIT_PNG); //allows png rendering
    this->spriteSurface = IMG_Load("spriteSheet.png");//load the duck sprite sheet to a surface
    this->spriteTexture = SDL_CreateTextureFromSurface(this->renderer, this->spriteSurface);//make that surface into a texture

    if(!this->cap.isOpened()) return; // check if we succeeded

    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    printf("Created Window\n");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED); // draw things to screen
    printf("Created Renderer\n");

    this->surface = SDL_GetWindowSurface(this->window);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface); // SDL_Texture - A structure that contains an efficient, driver-specific representation of pixel data.

    //this->world.addDuck(Duck(Radian(10), 20));
    //this->world.addDuck(Duck(Radian(20), 30));
    //this->world.addDuck(Duck(Radian(30), 10));
    //this->world.addDuck(Duck(Radian(20), 40));
    this->world.addDuck(Duck(Radian(90), 10));
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
        //printf("%f\n", i->getDistance());
        Radian offset(0);
        double duckX = (radarSize / 2) + i->getDistance() * cos((i->getAngle() + this->world.getPlayer()->angle + offset).toRad());
        double duckY = (radarSize / 2) - i->getDistance() * sin((i->getAngle() + this->world.getPlayer()->angle + offset).toRad());
        //printf("At %f rad, %f distance: (%f, %f)\n", i->getAngle().toRad(), i->getDistance(), duckX, duckY);
        uint8_t red;
        uint8_t green;
        uint8_t blue;

        if (i->isVisible(world.getPlayer()->getAngle(), world.getPlayer()->getFov())) {
            //printf("Duck is visible.\n");
            red = 0x00;
            green = 0xFF;
            blue = 0x00;
        }
        else {
            //printf("Duck is INVISIBLE!\n");
            red = 0xFF;
            green = 0x00;
            blue = 0x00;
        }
        filledCircleRGBA(this->renderer,
                radarOriginX + duckX,
                radarOriginY + duckY,
                3,
                red, green, blue,
                0xFF);
    }




}

void Game::drawDucks() {
    for (list<Duck>::iterator iDuck = this->world.getDuckIterator(); iDuck != this->world.getDuckEnd(); iDuck++) {

        // Only worry about drawing the duck if it's visible
        if (iDuck->isVisible(world.getPlayer()->getAngle(), world.getPlayer()->getFov())) {

            // Get projection vector
            double player_x = 10 * cos(world.getPlayer()->getAngle().toRad());
            double player_y = 10 * sin(world.getPlayer()->getAngle().toRad());

            double duck_x = iDuck->getDistance() * cos(iDuck->getAngle().toRad());
            double duck_y = iDuck->getDistance() * sin(iDuck->getAngle().toRad());

            double dotproduct = (player_x * duck_x) + (player_y * duck_y);
            double magnitude = sqrt(player_x * player_x + player_y * player_y) * sqrt(duck_x * duck_x + duck_y * duck_y);

            double projection_scalar = dotproduct / magnitude;

            double proj_vector_x = player_x * projection_scalar;
            double proj_vector_y = player_y * projection_scalar;


            //double ortho_vector_x = proj_vector_x - duck_x;
            //double ortho_vector_y = proj_vector_y - duck_y;
            double ortho_vector_x = duck_x - proj_vector_x;
            double ortho_vector_y = duck_y - proj_vector_y;

            double ortho_magnitude = sqrt(pow(ortho_vector_x, 2) + pow(ortho_vector_y,2));

            //printf("DUCK ORTHO VECTOR: %f %f\n", ortho_vector_x, ortho_vector_y);
            printf("DUCK ORTHO MAGNITUDE: %f\n", ortho_magnitude);

        }
            //typeNum = iDuck->getType();
            //SDL_Rect duckSrcRect = { typeNum * 64, 0, 64, 64 };

            //SDL_Rect duckDstRect = {288, 208, 64 * (typeNum + 1), 64 * (typeNum + 1)};

            //Uint32 ticks = SDL_GetTicks();
            //if (ticks % 500 == 0)
            //{
                //typeNum++;//enumerate
                //typeNum = (typeNum % 4);//max the typenum at 3
                //iDuck->setType(typeNum);
            //}

            //SDL_RenderCopy(this->renderer, this->spriteTexture, &duckSrcRect, &duckDstRect);
        }
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
                            this->world.getPlayer()->turnLeft(Radian(1));
                            break;
                        case SDLK_RIGHT:
                            printf("Turning right.\n");
                            this->world.getPlayer()->turnRight(Radian(1));
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
