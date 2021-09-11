#ifndef WORLD_H
#define WORLD_H
#include <vector>
#include <array>
#include "Object.h"
#include "TempObject.h"
#include "Wall.h"

class World {

public: 

    World();
    ~World();

    void updateObjects(float deltatime);
    void handleCollisions();
    void render(sf::RenderWindow& window);

    void addObject(Object o);

    void setIsAddingNewVertex(bool b);
    void setTempObject(TempObject* t);

private:

    bool isAddingNewVertex;
    TempObject* tempObject;
    std::vector<Object> objects;
    std::array<Wall, 4> walls{};

}; 

#endif