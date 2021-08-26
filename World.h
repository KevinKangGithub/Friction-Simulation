#ifndef WORLD
#define WORLD
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
    void handleCollisions();
    void addObject(Object o);

    TempObject* tempObject;

private:

    std::vector<Object> objects;

}; 

#endif