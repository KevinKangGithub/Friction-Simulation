#include "TempObject.h"

TempObject::TempObject() {
    setPrimitiveType(sf::LineStrip);
}

TempObject::~TempObject() {}

void TempObject::addPoint(sf::Vector2i point) {
    append(sf::Vertex(sf::Vector2f(point.x, point.y), sf::Color::White));
}
