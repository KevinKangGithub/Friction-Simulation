#include "VectorMath.h"

using namespace VectorMath;

float VectorMath::crossProduct(sf::Vector2f& v1, sf::Vector2f& v2) {
    return (v1.x * v2.y) - (v1.y * v2.x); //returns the z-coordinate of the cross product https://www.mathsisfun.com/algebra/vectors-cross-product.html
}

float VectorMath::dotProduct(sf::Vector2f& v1, sf::Vector2f& v2) {
    return (v1.x * v1.y) + (v1.y * v2.y);
}

float VectorMath::distanceSquared(sf::Vector2f& v1, sf::Vector2f& v2) {
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v1.y) * (v1.y - v1.y);
}
