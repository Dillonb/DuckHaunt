#include <cstdlib>
#include <cstdio>
#include "game.h"

using namespace std;

int main(int argc, char** argv) {
    int exitStatus;

    do {
        Game game(640,480);
        exitStatus = game.run();
    } while (exitStatus == EXIT_RESTART);
}
