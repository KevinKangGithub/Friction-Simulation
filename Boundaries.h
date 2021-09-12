#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include "Collideable.h"

class Object;

class Boundaries : public Collideable {
public:

    Boundaries();
    ~Boundaries();

    bool detectObjectCollision(const Object& o) override;

private:
};

#endif
