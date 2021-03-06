#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"
#include "World.h"
#include "VectorMath.h"

/*
    TODO:
    - add surface class
      - add ability to draw a "surface" with right mouse button which objects can collide with
    - 
    - fix object collisions with the window
    - add object collision with each other
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Friction Simulation");
    World world;
    TempObject tempObject;
    tempObject.addPoint(sf::Vector2i(20, 20));
    tempObject.addPoint(sf::Vector2i(20, 40));
    tempObject.addPoint(sf::Vector2i(40, 40));
    tempObject.addPoint(sf::Vector2i(40, 20));
    tempObject.addPoint(sf::Vector2i(20, 20));
    world.setTempObject(&tempObject);
    world.addObject(tempObject.toObject());
    tempObject = TempObject();
    sf::Clock clock;
    sf::Vector2i mousePos;
    sf::Event event;

    float deltatime = 0.f;

    while (window.isOpen()) {
        deltatime = clock.restart().asSeconds(); //clock.restart() also returns the elapsed time
        mousePos = sf::Mouse::getPosition(window);
        tempObject.setTempLinePos2(mousePos);
        
        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                return EXIT_SUCCESS;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    tempObject.addPoint(mousePos);
                    if (tempObject.getVertexCount() > 2 && VectorMath::isCloseEnough(tempObject.getInitialPos(), mousePos)) {
                        world.addObject(tempObject.toObject());
                        tempObject = TempObject();
                    }
                }

                world.setIsAddingNewVertex(false);
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    world.setIsAddingNewVertex(true);
                    if (!tempObject.getHasPoints()) {
                        tempObject.addPoint(mousePos);
                        tempObject.setInitialPos(mousePos);
                    }
                }
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape && tempObject.getVertexCount() > 0) tempObject = TempObject();
                break;

            case sf::Event::Resized:
                sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                window.setView(sf::View(visibleArea));
                break;
            }
        }

        world.updateObjects(deltatime); //update object positions, but do not render the changes

        window.clear();
        world.render(window); //draw the updated objects
        window.display();
    }

    return EXIT_SUCCESS;
}
