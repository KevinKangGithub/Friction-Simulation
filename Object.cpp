#include "Object.h"
#include "Constants.h"

Object::Object(sf::Vector2f &pos, sf::Vector2f &size, float rv) {
    setOrigin(size.x / 2, size.y / 2);
    setPosition(pos);
    setSize(size);
    setRotationalVelocity(rv);
};
Object::~Object() {};

void Object::updatePos(float deltatime) {
    float accelX = -velocity.x * (1 - FRICTION) * deltatime;
    float accelY = -velocity.y * (1 - FRICTION) * deltatime + GRAVITY * deltatime;
    float accelR = -rotationalVelocity * (1 - FRICTION) * deltatime;
    setVelocity(sf::Vector2f(velocity.x + accelX, velocity.y + accelY));
    setRotationalVelocity(rotationalVelocity + accelR);
    move(velocity);
    rotate(rotationalVelocity);
}

void Object::setVelocity(sf::Vector2f v) {
    velocity = v;
}

sf::Vector2f Object::getVelocity() const {
    return velocity;
}

void Object::setRotationalVelocity(float rv) {
    rotationalVelocity = rv;
}

float Object::getRotationalVelocity() const {
    return rotationalVelocity;
}
