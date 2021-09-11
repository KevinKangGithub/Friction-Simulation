#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H
#include "SFML/Graphics.hpp"

class Collideable {

public:

    Collideable();
    virtual ~Collideable() = 0;
    bool virtual detectObjectCollision(const sf::ConvexShape& o) = 0;

 };

#endif
