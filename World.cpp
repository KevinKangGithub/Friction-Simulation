#include "World.h"
#include "Constants.h"
#include "Wall.h"
#include <array>
#include <iostream>
#include "VectorMath.h"

World::World() {
    tempObject = nullptr;
    isAddingNewVertex = false;
    walls = {
        Wall(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(1, WINDOW_HEIGHT))), //left wall
        Wall(sf::FloatRect(sf::Vector2f(WINDOW_WIDTH, 0.f), sf::Vector2f(1, WINDOW_HEIGHT))), //right wall
        Wall(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(WINDOW_WIDTH, 1))), //top wall
        Wall(sf::FloatRect(sf::Vector2f(0.f, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH, 1))), //bottom wall
    };
};

World::~World() {
    //delete tempObject;
};

void World::handleCollisions() {
    for (size_t i = 0; i < objects.size(); i++) {
        Object& obj = objects.at(i);

        for (size_t j = 0; j < walls.size(); j++) {
            if (walls[i].detectObjectCollision(obj)) {
            }
        }

        /* 
        * this loop is made liks this to prevent objects from colliding with themself and
        * prevents double checking collisions (dont care if object 2 collides with object 1 
        * because object 1 already checks with object 2) 
        */

        for (size_t j = i + i; j < objects.size() - i - 1; j++) {  
            Object& obj2 = objects.at(j);
            if (obj.detectObjectCollision(obj2)) {
                std::cout << "obj colliison \n";
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
