#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class TempObject {

public:

    TempObject();
    ~TempObject();
    void addPoint(sf::Vector2i point);
    void setInitialPos(sf::Vector2i point);
    void drawVertexArray(sf::RenderWindow &w);
    sf::Vector2i getInitialPos() const;
    Object toObject();
    void setTempLinePos2(sf::Vector2i);

    size_t getVertexCount() const;
    sf::VertexArray getTempLine() const;

private:

    sf::Vector2i initialPos;
    sf::VertexArray vertexArray;
    sf::VertexArray tempLine;

};

