#include "Object.h"
#include "Constants.h"
#include <vector>
#include <iostream>

sf::Vector2f Object::calcTopLeft(Object& o) {
    //algorithm to find the top left bounding corner of the object in global coordinates
    //minimize these two points, so initialize them to be larger that possible;
    float leftMostPoint = WINDOW_WIDTH + 1;
    float highestPoint = WINDOW_HEIGHT + 1;
    float xPos, yPos;
    for (size_t i = 0; i < o.getPointCount(); i++) {
        xPos = o.getPoint(i).x;
        yPos = o.getPoint(i).y;
        if (xPos < leftMostPoint) leftMostPoint = xPos;
        if (yPos < highestPoint) highestPoint = yPos;
    }
   
    return sf::Vector2f(leftMostPoint, highestPoint);
}

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

    xi = o.getPoint(o.getPointCount() - 1).x;
    xi1 = o.getPoint(0).x;
    yi = o.getPoint(o.getPointCount() - 1).y;
    yi1 = o.getPoint(0).y;
    Cx += (xi + xi1) * (xi * yi1 - xi1 * yi);
    Cy += (yi + yi1) * (xi * yi1 - xi1 * yi);

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
    
    totalMass += o.getPoint(pointCount - 1).x * o.getPoint(0).y;
    totalMass -= o.getPoint(0).x * o.getPoint(pointCount - 1).y;
    return std::abs(totalMass / 2);
}

Object::Object(std::vector<sf::Vector2f> points, sf::Vector2f pos, float rv) {
    setPointCount(points.size());
    
    for (size_t i = 0; i < points.size(); i++) {
        setPoint(i, points.at(i));
    }

    mass = calcMass(*this);
    sf::Vector2f globalCenterOfMass = calcCentroid(*this);
    sf::Vector2f globalTopLeft = calcTopLeft(*this);
    std::cout << "gCen - gTL = {" << std::to_string(globalCenterOfMass.x) << " - " << std::to_string(globalTopLeft.x) << +", " << std::to_string(globalCenterOfMass.y) << " - " << std::to_string(globalTopLeft.y) << +"}\n";
    setPosition(pos);
    setOrigin(globalCenterOfMass.x - globalTopLeft.x, globalCenterOfMass.y - globalTopLeft.y);
    setRotationalVelocity(0.f);
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
