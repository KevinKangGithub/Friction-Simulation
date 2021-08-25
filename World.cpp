#include "World.h"

World::World() {};
World::~World() {};

std::vector<Object> World::getObjects() const {
    return objects;
}

void World::handleCollisions() {
    for (size_t i = 0; i < objects.size(); i++) {
        Object& obj = objects.at(i);
/*
        //left collision
        if (getPosition().x < getRadius()) {
            setPosition(getRadius(), getPosition().y);
            setVelocity(-getVelocity().x, getVelocity().y);
        }
        //right bound collision
        else if (getPosition().x > WINDOW_WIDTH - getRadius()) {
            setPosition(WINDOW_WIDTH - getRadius(), getPosition().y);
            setVelocity(-getVelocity().x, getVelocity().y);
        }
        //top collision
        if (getPosition().y < getRadius()) {
            setPosition(getPosition().x, getRadius());
            setVelocity(getVelocity().x, -getVelocity().y);
        }
        //bottom collision
        else if (getPosition().y > WINDOW_HEIGHT - getRadius()) {
            setPosition(getPosition().x, WINDOW_HEIGHT - getRadius());
            setVelocity(getVelocity().x, -getVelocity().y);
        }
        */
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
