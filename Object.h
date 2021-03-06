#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>
#include "Collideable.h"

class Object : public Collideable, public sf::ConvexShape {
public:

    Object(std::vector<sf::Vector2f> points, sf::Vector2f pos, float rv = 0);
    ~Object();

    void updatePos(float deltatime);

    void setVelocity(sf::Vector2f v);
    void setRotationalVelocity(float v);
    
    sf::Vector2f getGlobalTransformedPoint(size_t i) const;
    sf::Vector2f getVelocity() const;
    float getRotationalVelocity() const;
    float getMass() const;

    bool detectObjectCollision(const Object& o) override;
    
private: 
    
    sf::Vector2f velocity;
    float rotationalVelocity; //degrees per second clockwise
    float mass;

};

#endif
