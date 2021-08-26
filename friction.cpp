#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "World.h"
#include "Renderer.h"
#include <vector>
#include <iostream>
/*
    TODO:
    - add surface class
      - add ability to draw a "surface" with right mouse button which objects can collide with
    - add ability to draw objects with different sizes
    - 
    - rotation of objects
    - fix object collisions with the window
    - add object collision with each other
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Friction Simulation");
    
    World world;
    Renderer renderer(world);
    TempObject tempObject;

    float deltatime = 0.f;
    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        
        deltatime = clock.restart().asSeconds(); //clock.restart() also returns the elapsed time


        while (window.pollEvent(event)) 
        {
            switch (event.type) {
                case sf::Event::Closed:
                window.close();
                return EXIT_SUCCESS;
            case sf::Event::MouseButtonReleased:

                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "mousePos: (" << std::to_string(sf::Mouse::getPosition(window).x) << ", " << std::to_string(sf::Mouse::getPosition(window).x) + ")\n";

                    tempObject.addPoint(sf::Mouse::getPosition(window));
                }
                
            case sf::Event::MouseButtonPressed:
                break;
            }

        }

        world.updateObjects(deltatime); //update object positions, but do not render the changes
        window.clear();
        renderer.render(window); //draw the updated objects
        window.draw(tempObject);
        window.display();
    }

    return EXIT_SUCCESS;
}
