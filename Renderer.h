#ifndef RENDERER
#define	RENDERER

#include <SFML/Graphics.hpp>
#include "World.h"

class Renderer
{
public:
    Renderer(World& world);
    ~Renderer();

    void render(sf::RenderWindow& window) const;
    void renderObjects(sf::RenderWindow& window) const;
    
private:
    World& world;
};

#endif
