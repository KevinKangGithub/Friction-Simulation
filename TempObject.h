#ifndef TEMPOBJECT_H
#define TEMPOBJECT_H
#include <SFML/Graphics.hpp>
#include "Object.h"

class TempObject {

public:

    TempObject();
    ~TempObject();
    Object toObject();

    void addPoint(sf::Vector2i point);
    void setInitialPos(sf::Vector2i point);
    void drawVertexArray(sf::RenderWindow &w);
    void drawTempLine(sf::RenderWindow& w);

    void setTempLinePos1(sf::Vector2i);
    void setTempLinePos2(sf::Vector2i);

    bool getHasPoints() const;
    sf::Vector2i getInitialPos() const;
    size_t getVertexCount() const;

private:

    sf::Vector2i initialPos;
    sf::VertexArray vertexArray;
    sf::VertexArray tempLine;
    bool hasPoints;

};

#endif
