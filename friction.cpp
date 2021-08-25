#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "World.h"
#include "Renderer.h"

/*
    TODO:
    - add surface class
      - add ability to draw a "surface" with right mouse button which objects can collide with
    - add ability to draw objects with different sizes
    - 
    - rotation of objects
    - object collisions with each other and the window
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Friction Simulation");
    
    World world;
    Renderer renderer(world);
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
                    sf::Vector2f mousePos(((float) (sf::Mouse::getPosition(window).x)), ((float) (sf::Mouse::getPosition(window).y)));
                    sf::Vector2f size(50.f, 50.f);

                    Object o = Object(mousePos, size);
                    o.setVelocity(sf::Vector2f(1.f, 1.f));
                    //add a new object, temp implementation for now
                    world.addObject(o);
                }
            }

        }

        world.updateObjects(deltatime); //update object positions, but do not render the changes
        window.clear();
        renderer.render(window); //draw the updated objects
        window.display();
    }

    return EXIT_SUCCESS;
}
