#pragma once
#include <SFML/Graphics.hpp>

namespace VectorMath {
    float crossProduct(sf::Vector2f &v1, sf::Vector2f &v2);
    float dotProduct(sf::Vector2f& v1, sf::Vector2f& v2);
    float distanceSquared(sf::Vector2f& v1, sf::Vector2f& v2);
}
