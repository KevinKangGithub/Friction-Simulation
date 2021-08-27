#include "TempObject.h"
#include <SFML/Graphics.hpp>

TempObject::TempObject() {
    vertexArray.setPrimitiveType(sf::LineStrip);
    tempLine.resize(2);
    tempLine.setPrimitiveType(sf::Lines);
}

TempObject::~TempObject() {}

void TempObject::addPoint(sf::Vector2i point) {
    sf::Vertex newVertex = sf::Vertex(sf::Vector2f((float) point.x, (float) point.y), sf::Color::White);
    vertexArray.append(newVertex);
    tempLine[0] = newVertex;
}

void TempObject::setInitialPos(sf::Vector2i v) {
    initialPos = v;
}

void TempObject::setTempLinePos2(sf::Vector2i v) {
    tempLine[1] = sf::Vertex(sf::Vector2f((float) v.x, (float) v.y), sf::Color::White);
}

void TempObject::drawVertexArray(sf::RenderWindow &w) {
    w.draw(vertexArray);
}

sf::Vector2i TempObject::getInitialPos() const {
    return sf::Vector2i(vertexArray[0].position.x, vertexArray[0].position.y);
}

Object TempObject::toObject() {
    std::vector<sf::Vector2f> points;

    for (size_t i = 0; i < vertexArray.getVertexCount(); i++) {
        points.push_back(sf::Vector2f(vertexArray[i].position.x - initialPos.x, vertexArray[i].position.y - initialPos.y));
    }
 
    return Object(points, sf::Vector2f((float) initialPos.x, (float) initialPos.y));
}

size_t TempObject::getVertexCount() const {
    return vertexArray.getVertexCount();
}

sf::VertexArray TempObject::getTempLine() const {
    return tempLine;
}
