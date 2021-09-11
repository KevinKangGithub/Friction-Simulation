#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include "Collideable.h"

class Wall : public Collideable {
public:

    Wall();
    Wall(sf::FloatRect rect);
    ~Wall();

    bool detectObjectCollision(const sf::ConvexShape& o) override;

private:
    std::vector<sf::Vector2f> corners;
};

#endif
