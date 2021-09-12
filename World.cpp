#include "World.h"
#include "Constants.h"
#include "Boundaries.h"
#include <array>
#include "VectorMath.h"

World::World() {
    tempObject = nullptr;
    isAddingNewVertex = false;
    bounds = Boundaries();
};

World::~World() {
    //delete tempObject;
};

void World::handleCollisions() {
    for (size_t i = 0; i < objects.size(); i++) {
        Object& obj = objects.at(i);

        if (bounds.detectObjectCollision(obj)) {
            //handle collision
        }

        /* 
        * this loop is made liks this to prevent objects from colliding with themself and
        * prevents double checking collisions (dont care if object 2 collides with object 1 
        * because object 1 already checks with object 2) 
        */

        for (size_t j = i + 1; j < objects.size() - i; j++) {  
            Object& obj2 = objects.at(j);
            if (obj.detectObjectCollision(obj2)) {
                //handle collision
            }
        }
    }
}

void World::updateObjects(float deltatime) {
    for (size_t i = 0; i < objects.size(); i++) {
        objects.at(i).updatePos(deltatime);
        handleCollisions();
    }
}

void World::addObject(Object o) {
    objects.push_back(o);
}

void World::setIsAddingNewVertex(bool b) {
    isAddingNewVertex = b;
}

void World::setTempObject(TempObject* t) {
    tempObject = t;
}

void World::render(sf::RenderWindow& window) {
    for (const Object &obj : objects) {
        window.draw(obj);
    }

    TempObject t = *tempObject;
    if (t.getHasPoints()) t.drawVertexArray(window);
    if (isAddingNewVertex) t.drawTempLine(window);
}
