#pragma once

#include <SFML/Graphics.hpp>

class Object :
    public sf::RectangleShape
{
public:
    Object(sf::Vector2f &pos, sf::Vector2f &size, float rv = 0.f);
    ~Object();

    void updatePos(float deltatime);

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity() const;

    void setRotationalVelocity(float v);
    float getRotationalVelocity() const;

private: 
    
    sf::Vector2f velocity;
    float rotationalVelocity; //degrees per second

};

