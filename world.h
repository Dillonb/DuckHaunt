#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <cstdio>
#include "duck.h"
#include "player.h"

using namespace std;

class World {
    Player player;

    public:
        list<Duck> ducks;
        World();

        void addDuck(Duck);

        list<Duck>::iterator getDuckIterator();
        list<Duck>::iterator getDuckEnd();

        Player* getPlayer();
};

#endif
