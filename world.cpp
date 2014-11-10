#include "world.h"

void World::addDuck(Duck d) {
    printf("Added a duck.\n");
    this->ducks.push_front(d);
}


list<Duck>::iterator World::getDuckIterator() {
    return this->ducks.begin();
}
list<Duck>::iterator World::getDuckEnd() {
    return this->ducks.end();
}

World::World() {
    // Do nothing
}
