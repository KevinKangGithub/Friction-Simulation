#include "World.h"
#include "Constants.h"

World::World() {
    tempObject = nullptr;
};
World::~World() {};

std::vector<Object> World::getObjects() const {
    return objects;
}

void World::handleWallCollision(Object& o) {
    //seperating axis theorem http://programmerart.weebly.com/separating-axis-theorem.html
    
    sf::FloatRect bound = o.getGlobalBounds();
    float windowMinX = 0;
    float windowMaxX = WINDOW_WIDTH - bound.width;
    float windowMinY = 0;
    float windowMaxY = WINDOW_HEIGHT - bound.height;
    bool inBounds = false;
    


    if (inBounds) {
        //do seperating axis theorem
    }
}

void World::handleObjectCollision(Object& o1, Object& o2) {

}

void World::handleCollisions() {
    for (size_t i = 0; i < objects.size(); i++) {
        Object& obj = objects.at(i);
        handleWallCollision(obj);
        
        /* 
        * this loop is made liks this to prevent objects from colliding with themself and
        * prevents double checking collisions (dont care if object 2 collides with object 1 
        * because object 1 already checks with object 2) 
        */

        for (size_t j = i + i; j < objects.size() - i - 1; j++) {  
            Object& obj2 = objects.at(j);
            handleObjectCollision(obj, obj2);
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
