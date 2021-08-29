#include "Object.h"
#include "Constants.h"
#include <vector>

sf::Vector2f Object::calcCentroid(Object& o) {
    // https://en.wikipedia.org/wiki/Centroid#Of_a_polygon
    // point MUST be organized in counter-clockwise order for this to work
    float A = 1.f / (6.f * o.getMass());
    float Cx = 0.f;
    float Cy = 0.f;
    float xi, xi1, yi, yi1;

    for (size_t i = 0; i < o.getPointCount() - 1; i++) {
        xi = o.getPoint(i).x;
        xi1 = o.getPoint(i + 1).x;
        yi = o.getPoint(i).y;
        yi1 = o.getPoint(i + 1).y;

        Cx += (xi + xi1) * (xi * yi1 - xi1 * yi);
        Cy += (yi + yi1) * (xi * yi1 - xi1 * yi);
    }

    return sf::Vector2f(Cx * A, Cy * A);
}

float Object::calcMass(Object &o) {
    // https://en.wikipedia.org/wiki/Shoelace_formula
    // point must be organized in counter-clockwise order to get a positive result

    float totalMass = 0.f;
    size_t pointCount = o.getPointCount();

    for (size_t i = 0; i < pointCount - 1; i++) {
        totalMass += o.getPoint(i).x * o.getPoint(i + 1).y;
        totalMass -= o.getPoint(i + 1).x * o.getPoint(i).y;
    }
    
    return (totalMass / 2);
}

Object::Object(std::vector<sf::Vector2f> points, sf::Vector2f pos, float rv) {
    setPointCount(points.size());
    
    for (size_t i = 0; i < points.size(); i++) {
        setPoint(i, points.at(i));
    }

    mass = calcMass(*this);
    sf::Vector2f localCenterOfMass = calcCentroid(*this);
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
