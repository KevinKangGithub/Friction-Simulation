#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TempObject : public sf::VertexArray
{
public:

    TempObject();
    ~TempObject();
    void addPoint(sf::Vector2i point);

private:

    sf::Vector2i initialPos = sf::Vector2i();

};

