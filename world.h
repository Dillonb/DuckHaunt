#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <cstdio>
#include "duck.h"

using namespace std;

class World {
    list<Duck> ducks;

    public:
        World();

        void addDuck(Duck);

        list<Duck>::iterator getDuckIterator();
};

#endif
