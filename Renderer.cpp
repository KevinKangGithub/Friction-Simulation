#include "Renderer.h"

Renderer::Renderer(World& world) : world(world) {};
Renderer::~Renderer() {};

void Renderer::render(sf::RenderWindow& window) const {
    renderObjects(window);
}

void Renderer::renderObjects(sf::RenderWindow& window) const {
    for (Object obj : world.getObjects()) {
        window.draw(obj);
    }
}
