#include "TempObject.h"
#include <SFML/Graphics.hpp>
#include <stack>
#include "VectorMath.h"

TempObject::TempObject() {
    vertexArray.setPrimitiveType(sf::LineStrip);
    tempLine.resize(2);
    tempLine.setPrimitiveType(sf::Lines);
    hasPoints = false;
}

TempObject::~TempObject() {};

Object TempObject::toObject() {
    std::vector<sf::Vector2i> points;

    for (size_t i = 0; i < vertexArray.getVertexCount() - 1; i++) { //don't include the last duplicate point for convex hull algorithm
        points.push_back(sf::Vector2i(
            static_cast<int>(vertexArray[i].position.x - initialPos.x), //these should be integers anyway since it comes from mouse posisions
            static_cast<int>(vertexArray[i].position.y - initialPos.y))
        );
    }
 
    VectorMath::ConvexHullSolver convexHullSolver(points);
    return Object(convexHullSolver.getConvexHull(), VectorMath::intToFloatVector(initialPos), 0.1f);
}

void TempObject::addPoint(sf::Vector2i point) {
    if (!hasPoints) hasPoints = true;
    sf::Vertex newVertex = sf::Vertex(sf::Vector2f((float) point.x, (float) point.y), sf::Color::White);
    vertexArray.append(newVertex);
    tempLine[0] = newVertex;
}

void TempObject::drawVertexArray(sf::RenderWindow &w) {
    w.draw(vertexArray);
}

void TempObject::drawTempLine(sf::RenderWindow& w) {
    w.draw(tempLine);
}

void TempObject::setInitialPos(sf::Vector2i v) {
    initialPos = v;
}

void TempObject::setTempLinePos1(sf::Vector2i v) {
    tempLine[0] = sf::Vertex(sf::Vector2f((float) v.x, (float) v.y), sf::Color::White);
}

void TempObject::setTempLinePos2(sf::Vector2i v) {
    tempLine[1] = sf::Vertex(sf::Vector2f((float) v.x, (float) v.y), sf::Color::White);
}

bool TempObject::getHasPoints() const {
    return hasPoints;
}

sf::Vector2i TempObject::getInitialPos() const {
    return initialPos;
}

size_t TempObject::getVertexCount() const {
    return vertexArray.getVertexCount();
}

