#include <vector>
#include "Object.h"
#include "VectorMath.h"
#include "Constants.h"
#include "Projection.h"

Object::Object(std::vector<sf::Vector2f> points, sf::Vector2f pos, float rv) {
    setPointCount(points.size());
    
    for (size_t i = 0; i < points.size(); i++) {
        setPoint(i, points.at(i));
    }

    mass = VectorMath::calcArea(*this);
    sf::Vector2f localCenterOfMass = VectorMath::calcCentroid(*this);
    setOrigin(localCenterOfMass);
    setPosition(pos + localCenterOfMass);
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

sf::Vector2f Object::getGlobalTransformedPoint(size_t i) const {
    return getTransform().transformPoint(getPoint(i));
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

bool Object::detectObjectCollision(const Object& o) {
    std::vector<sf::Vector2f> o1axes = VectorMath::calcNormals(*this);
    std::vector<sf::Vector2f> o2axes = VectorMath::calcNormals(o);

    for (size_t i = 0; i < o1axes.size(); i++) {
        sf::Vector2f axis = o1axes[i];

        Projection thisProjection = VectorMath::projectVector(axis, *this);
        Projection objectProjection = VectorMath::projectVector(axis, o);

        if (!(objectProjection.max < thisProjection.min || thisProjection.max < objectProjection.min)) return false;

    }
    return true;
}
