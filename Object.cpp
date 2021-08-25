#include "Object.h"
#include "Constants.h"
#include <vector>

sf::Vector2f Object::calcCentroid(Object &o) {
    // https://en.wikipedia.org/wiki/Centroid#Of_a_polygon

    float A = 1 / (6 * calcMass(o));
    float Cx = 0.f;
    float Cy = 0.f;

    for (size_t i = 0; i < o.getPointCount() - 1; i++) {
        float xi = o.getPoint(i).x;
        float xi1 = o.getPoint(i + 1).x;
        float yi = o.getPoint(i).y;
        float yi1 = o.getPoint(i + 1).y;

        Cx += (xi + xi1) * (xi * yi1 - xi1 * yi);
        Cy += (yi + yi1) * (xi * yi1 - xi1 * yi);
    }

    return sf::Vector2f(Cx * A, Cy * A);
}

float Object::calcMass(Object &o) {
    // https://en.wikipedia.org/wiki/Shoelace_formula

    float totalMass = 0.f;
    size_t pointCount = o.getPointCount();
    
    for (size_t i = 0; i < pointCount - 1; i++) {
        totalMass += o.getPoint(i).x * o.getPoint(i + 1).y;
        totalMass -= o.getPoint(i + 1).x * o.getPoint(i).y;
    }
    
    totalMass += o.getPoint(pointCount).x * o.getPoint(0).y;
    totalMass -= o.getPoint(0).x * o.getPoint(pointCount).y;

    return totalMass / 2;
}

Object::Object(std::vector<sf::Vector2f> points, float rv) {
    setPointCount(points.size());
    
    for (size_t i = 0; i < points.size(); i++) {
        setPoint(i, points.at(i));
    }

    sf::Vector2f centerOfMass = calcCentroid(*this);
    setOrigin(centerOfMass);
    setPosition(centerOfMass);
    mass = calcMass(*this);
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

float Object::getMass() const {
    return mass;
}
