#pragma once

#include <SFML/Graphics.hpp>

class Object :
    public sf::RectangleShape
{
public:
    Object(sf::Vector2f &pos, sf::Vector2f &size);
    ~Object();

    void updatePos(float deltatime);

    void setVelocity(sf::Vector2f v);
    sf::Vector2f getVelocity();

private: 
    
    sf::Vector2f velocity;

};

