#include "World.h"
#include "Constants.h"

World::World() {};
World::~World() {};

std::vector<Object> World::getObjects() const {
    return objects;
}

void World::handleWallCollision(Object& o) {
    float posX = o.getPosition().x;
    float posY = o.getPosition().y;
    float windowMinX = 0.f;
    float windowMaxX = WINDOW_WIDTH - o.getSize().x;
    float windowMinY = 0.f;
    float windowMaxY = WINDOW_HEIGHT - o.getSize().y;

    if (posX < windowMinX) {
        o.setPosition(windowMinX, posY);
        o.setVelocity(sf::Vector2f(-o.getVelocity().x, o.getVelocity().y));
    } 
    else if (posX > windowMaxX) {
        o.setPosition(windowMaxX, posY);
        o.setVelocity(sf::Vector2f(-o.getVelocity().x, o.getVelocity().y));
    }
    if (posY < windowMinY) {
        o.setPosition(posX, windowMinY);
        o.setVelocity(sf::Vector2f(o.getVelocity().x, -o.getVelocity().y));
    }
    if (posY > windowMaxY) {
        o.setPosition(posX, windowMaxY);
        o.setVelocity(sf::Vector2f(o.getVelocity().x, -o.getVelocity().y));
    }
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
        this->handleCollisions();
    }
}

void World::addObject(Object o) {
    objects.push_back(o);
}
