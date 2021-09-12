#ifndef BOUNDARIES_H
#define BOUNDARIES_H
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
