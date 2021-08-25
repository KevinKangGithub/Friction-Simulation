#pragma once

#include <SFML/Graphics.hpp>

class Object :
    public sf::ConvexShape
{
public:
    Object(std::vector<sf::Vector2f> points, float rv = 0);
    ~Object();

    static sf::Vector2f calcCentroid(Object &o); //https://en.wikipedia.org/wiki/Centroid
    static float calcMass(Object &o);

    void updatePos(float deltatime);

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity() const;

    void setRotationalVelocity(float v);
    float getRotationalVelocity() const;

    float getMass() const;

private: 
    
    sf::Vector2f velocity;
    float rotationalVelocity; //degrees per second
    float mass;

};

