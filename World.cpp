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

    /*
    float posX = o.getPosition().x;
    float posY = o.getPosition().y;
    float windowMinX = o.getSize().x / 2;
    float windowMaxX = WINDOW_WIDTH - (o.getSize().x / 2);
    float windowMinY = o.getSize().y / 2;
    float windowMaxY = WINDOW_HEIGHT - (o.getSize().y / 2);
    float vx = o.getVelocity().x;
    float vy = o.getVelocity().y;

    if (posX < windowMinX) {
        o.setPosition(windowMinX, posY);
        o.setVelocity(sf::Vector2f(-vx * (1 - FRICTION), vy * (1 - FRICTION)));
    } 
    else if (posX > windowMaxX) {
        o.setPosition(windowMaxX, posY);
        o.setVelocity(sf::Vector2f(-vx * (1 - FRICTION), vy * (1 - FRICTION)));
    }
    if (posY < windowMinY) {
        o.setPosition(posX, windowMinY);
        o.setVelocity(sf::Vector2f(vx * (1 - FRICTION), -vy * (1 - FRICTION)));
    }
    else if (posY > windowMaxY) {
        o.setPosition(posX, windowMaxY);
        o.setVelocity(sf::Vector2f(vx * (1 - FRICTION), -vy * (1 - FRICTION)));
    }
    */
}

void World::handleCollisions() {
    for (size_t i = 0; i < objects.size(); i++) {

        Object& obj = objects.at(i);
        handleWallCollision(obj);
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
