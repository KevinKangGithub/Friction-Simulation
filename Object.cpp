#include <vector>
#include "Object.h"
#include "VectorMath.h"
#include "Constants.h"

Object::Object(std::vector<sf::Vector2f> points, sf::Vector2f pos, float rv) {
    setPointCount(points.size());
    
    for (size_t i = 0; i < points.size(); i++) {
        setPoint(i, points.at(i));
    }

    mass = VectorMath::calcArea(*this);
    sf::Vector2f localCenterOfMass = VectorMath::calcCentroid(*this);
    setPosition(pos);
    setOrigin(localCenterOfMass.x, localCenterOfMass.y);
    setRotationalVelocity(rv);
};
Object::~Object() {};

void Object::updatePos(float deltatime) {
    float accelX = 0.f;//-velocity.x * (1.f - FRICTION) * deltatime;
    float accelY = 0.f;//-velocity.y * (1.f - FRICTION) * deltatime + GRAVITY * deltatime;
    float accelR = 0.f;//-rotationalVelocity * (1.f - FRICTION) * deltatime;
    setVelocity(sf::Vector2f(velocity.x + accelX, velocity.y + accelY));
    setRotationalVelocity(rotationalVelocity + accelR);
    move(velocity);
    rotate(rotationalVelocity);
}

void Object::setVelocity(sf::Vector2f v) {
    velocity = v;
}

void Object::setRotationalVelocity(float rv) {
    rotationalVelocity = rv;
}

sf::Vector2f Object::getVelocity() const {
    return velocity;
}

float Object::getRotationalVelocity() const {
    return rotationalVelocity;
}

float Object::getMass() const {
    return mass;
}
