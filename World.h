#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Object.h"
#include "TempObject.h"

class World {

public: 
    World();
    ~World();

    void updateObjects(float deltatime);
    void handleWallCollision(Object& o);
    void handleObjectCollision(Object& o1, Object& o2);
    void handleCollisions();
    void render(sf::RenderWindow& window);

    void addObject(Object o);

    void setIsAddingNewVertex(bool b);
    void setTempObject(TempObject* t);

private:

    bool isAddingNewVertex;
    TempObject* tempObject;
    std::vector<Object> objects;

}; 

#endif