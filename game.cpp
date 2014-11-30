#include "game.h"

Game::Game(int w, int h) {
    this->cap = VideoCapture(0);
    this->width = w;
    this->height = h;
    this->radarSize = w / 7;


    if(!this->cap.isOpened()) {
        printf("FATAL ERROR: Failed to open webcam.\n");
        exit(EXIT_FAILURE); // Exit with an error code.
    }

    this->window = SDL_CreateWindow("Duck Haunt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    printf("Created Window\n");
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED); // draw things to screen
    printf("Created Renderer\n");

    IMG_Init(IMG_INIT_PNG); //allows png rendering

    this->spriteTexture = IMG_LoadTexture(this->renderer, "sprites/spriteSheet.png"); // Load the spritesheet directly into a texture
    this->surface = SDL_GetWindowSurface(this->window);
    this->texture = SDL_CreateTextureFromSurface(this->renderer, this->surface); // SDL_Texture - A structure that contains an efficient, driver-specific representation of pixel data.

    this->world.addDuck(Duck(Radian(0), 10));
    this->world.addDuck(Duck(Radian(10), 30));
    this->world.addDuck(Duck(Radian(30), 20));
    this->world.addDuck(Duck(Radian(100), 40));
    printf("Added all ducks\n");
    this->lastTicks = SDL_GetTicks();
}

void Game::redraw() {
    this->cap >> this->image; // get a new frame from camera

    //convert it to SDL_Surface
    SDL_Texture* frame=SDL_CreateTextureFromSurface(this->renderer, convertToSDLSurface(this->image));
    SDL_RenderCopy(this->renderer, frame, NULL, NULL);
    SDL_DestroyTexture(frame); // No memory leaks here.
    //render the whole thing out to 0,0 coordinate
    //SDL_BlitSurface(frame,NULL,this->surface,NULL);
    //avoid memory leaks
    // SDL_FreeSurface(frame);

    // Fill screen with black (eventually draw output of webcam here)
    //printf("Drawing Webcam\n");

    drawDucks();
    //printf("Ducks Drawn\n");

    drawRadar();
    //printf("Radar Drawn\n");

    drawHealth();

    SDL_UpdateWindowSurface(this->window);
    //printf("Updated Surface\n");

    SDL_RenderPresent(this->renderer);


    double timeBetweenTicks = SDL_GetTicks() - this->lastTicks;
    printf("FPS: %f\n", 1000 * pow(timeBetweenTicks, -1));
    this->lastTicks = SDL_GetTicks();
}

void Game::drawRadar() {
    Vector2 radarPos(this->width - this->radarSize, 0);
    Vector2 radarOrigin(radarPos.x + (radarSize / 2), (radarSize / 2));

    // Draw the radar circle
    filledCircleRGBA(this->renderer, radarPos.x + (this->radarSize / 2), radarPos.y + (this->radarSize / 2), radarSize / 2, 0x00, 0x00, 0x00, 0x99);
    // Draw the dot for the player at the center
    filledCircleRGBA(this->renderer, radarOrigin.x, radarOrigin.y, 2, 0xFF, 0xFF, 0xFF, 0xFF);

    Vector2 playerDirection = this->world.getPlayer()->getVector();

    // Player angle
    lineRGBA(this->renderer, radarOrigin.x, radarOrigin.y, radarOrigin.x + (radarSize / 2) * playerDirection.x, radarOrigin.y - (radarSize / 2) * playerDirection.y, 0xFF, 0xFF, 0xFF, 0xFF);


    // Draw ducks on radar

    for (list<Duck>::iterator i = this->world.getDuckIterator(); i != this->world.getDuckEnd(); i++) {
        uint8_t red, green, blue;
        if (i->isVisible(*this->world.getPlayer())) {
            red = 0x00;
            green = 0xFF;
            blue = 0x00;
        }
        else {
            red = 0xFF;
            green = 0x00;
            blue = 0x00;
        }
        filledCircleRGBA(this->renderer,
                radarOrigin.x + i->position.toVector2().x,
                radarOrigin.y - i->position.toVector2().y,
                2,
                red, green, blue,
                0xFF);
    }
}

void Game::drawHealth() {
    int playerHealth = (this->world.getPlayer()->health);
    SDL_Rect healthSrcRect = { playerHealth * 64, 64, 64, 64 };
    SDL_Rect healthDstRect = { 0, 0, 128, 128 };
    //draw
    int result = SDL_RenderCopy(this->renderer, this->spriteTexture, &healthSrcRect, &healthDstRect); 
}

void Game::drawDucks() {
    for (list<Duck>::iterator duck = this->world.getDuckIterator(); duck != this->world.getDuckEnd(); duck++) {
        // Only worry about drawing the duck if it's visible
        if (duck->isVisible(*world.getPlayer())) {
            //typeNum = iDuck->getType();
            SDL_Rect duckSrcRect = { duck->getFrame() * 64, 0, 64, 64 };

            // a = Duck
            // b = Player
            //((a . b) / (b . b)) * b

            // Vector representation of the position of the duck
            Vector2 duckVector = duck->position.toVector2();
            // vector representation of the player's angle
            Vector2 playerVector = this->world.getPlayer()->getVector();

            // Polar coordinate of the edge of the player's FOV at the distance of the duck
            Polarcoord edgeFov = duck->position;
            edgeFov.theta = this->world.getPlayer()->angle + (this->world.getPlayer()->FOV / 2);

            //printf("Player FOV: %f\nPlayer FOV / 2: %f\nedgeFOV.theta: %f\nplayerAngle: %f\nDuck angle: %f\n", this->world.getPlayer()->FOV.radVal, (this->world.getPlayer()->FOV / 2).radVal, edgeFov.theta.radVal, this->world.getPlayer()->angle.radVal, duck->position.theta.radVal);

            // Vector representation of the edge of the player's FOV
            Vector2 edgeFovVector = edgeFov.toVector2();

            // Refer to the below image for the following variables:
            // Where a is the duck and b is the player:
            // https://upload.wikimedia.org/wikipedia/commons/9/98/Projection_and_rejection.png
            //
            // Projection vector (a1 on the image) of the edge of the FOV
            Vector2 edgeProjection = playerVector * (edgeFovVector.dot(playerVector) / playerVector.dot(playerVector));
            // Rejection vector (a2 on the image) of the edge of the FOV (the maximum size the duck rejection vector can be)
            Vector2 edgeRejection = edgeFovVector - edgeProjection;


            // Projection vector (a1 on the image) of the duck
            Vector2 projection = playerVector * (duckVector.dot(playerVector) / playerVector.dot(playerVector));
            // Rejection vector (a2 on the image) of the duck
            Vector2 rejection = duckVector - projection;

            //printf("Rejection: [%f,%f]\n", rejection.x, rejection.y);

            //printf("Magnitude of edge of fov rejection: %f\nMagnitude of duck rejection: %f\n", edgeRejection.magnitude(), rejection.magnitude());


            // A ratio between the two rejection vectors to determine where on the screen the duck should go
            double duckDistance = rejection.magnitude() / edgeRejection.magnitude();

            // Multiply it by half the width of the screen to get an actual pixel value
            duckDistance *= (this->width / 2);

            // Ensures the sign is correct
            duckDistance *= duckVector.rightOf(playerVector);



            //printf("Duck distance: %f\n", duckDistance);

            //printf("[%f, %f]\n", rejection.x, rejection.y);
            //printf("Projection magnitude: %f\n Rejection magnitude: %f\n", projection.magnitude(), rejection.magnitude());

            double scaleFactor = 1000 * (1.f / pow(duck->position.r, 2));

            //printf("********Scale factor: %f\n", scaleFactor);

            Vector2 duckSize(scaleFactor * 64.f, scaleFactor * 64.f);

            SDL_Rect duckDstRect = {
                ((this->width / 2) + (duckDistance)) - (duckSize.x / 2),
                (this->height / 2) - (duckSize.y / 2),
                duckSize.x,
                duckSize.y};
            //now taken care of in duck->update()
            //duck->setFrame((duck->getFrame()+1) % 4);
            int result = SDL_RenderCopy(this->renderer, this->spriteTexture, &duckSrcRect, &duckDstRect);

            if (result < 0)
                printf("Calling RenderCopy: %s\n", SDL_GetError());
        }
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
        for (list<Duck>::iterator duck = this->world.getDuckIterator(); duck != this->world.getDuckEnd(); duck++) {
            duck->update();
            // Logic for when ducks die
            if (duck->status != alive) {
                if (duck->status == attackedPlayer) {
                    // Lower player health
                    this->world.getPlayer()->loseHealth();
                    
                    if (this->world.getPlayer()->getHealth() <= 0) {
                        // Player has died.
                    }
                }
                else if (duck->status == killedByPlayer) {
                    // Raise player score
                }else if (duck->status == dead){
                    // Remove duck from list
                    duck = this->world.ducks.erase(duck);
                }
            }
        }
        // Ensure that the closer ducks are first in the list
        this->world.ducks.sort(Duck::compare_distance);
        this->world.ducks.reverse();
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
