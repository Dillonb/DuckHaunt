#include <cstdlib>
#include <cstdio>
#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    Game game(640,480);
    int exitStatus;

    do {
        exitStatus = game.run();
    } while (exitStatus == EXIT_RESTART);
}
