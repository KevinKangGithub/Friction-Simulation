#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include "Object.h"
#include "TempObject.h"

class World {

public: 
    World();
    ~World();
    
    std::vector<Object> getObjects() const;

    void updateObjects(float deltatime);
    void handleWallCollision(Object& o);
    void handleObjectCollision(Object& o1, Object& o2);
    void handleCollisions();
    void addObject(Object o);

    TempObject* tempObject;

private:

    std::vector<Object> objects;

}; 

#endif