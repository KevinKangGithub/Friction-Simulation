#ifndef COLLIDEABLE_H
#define COLLIDEABLE_H

class Object;

class Collideable {

public:

    Collideable();
    virtual ~Collideable() = 0;
    bool virtual detectObjectCollision(const Object& o) = 0;

 };

#endif
