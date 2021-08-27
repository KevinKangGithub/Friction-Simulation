#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "World.h"
#include "Renderer.h"
#include <vector>
/*
    TODO:
    - add surface class
      - add ability to draw a "surface" with right mouse button which objects can collide with
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
    world.tempObject = &tempObject;
    sf::Clock clock;
    sf::Vector2i mousePos;

    float deltatime = 0.f;
    bool addingNewVertex = false;

    while (window.isOpen()) 
    {
        sf::Event event;
        
        deltatime = clock.restart().asSeconds(); //clock.restart() also returns the elapsed time
        mousePos = sf::Mouse::getPosition(window);
        tempObject.setTempLinePos2(mousePos);
        
        while (window.pollEvent(event))
        {
            switch (event.type) {

            case sf::Event::Closed:
                window.close();
                return EXIT_SUCCESS;
            
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    tempObject.addPoint(mousePos);
                    
                    if (tempObject.getVertexCount() == 0) tempObject.setInitialPos(mousePos);

                    if (tempObject.getVertexCount() > 2 && tempObject.getInitialPos().x == mousePos.x && tempObject.getInitialPos().y == mousePos.y) { 
                        //TODO method to determine if the mouse is "close enough" to the first vertex position
                        //TODO method to sort points in clockwise or counterclockwise order for the centroid and mass methods to work correctly
                        world.addObject(tempObject.toObject());
                        tempObject = TempObject();
                    }
                }

                addingNewVertex = false;
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) addingNewVertex = true;
                break;
            }
        }

        world.updateObjects(deltatime); //update object positions, but do not render the changes
        window.clear();

        if (addingNewVertex) {
            window.draw(tempObject.getTempLine());
        }

        renderer.render(window); //draw the updated objects
        window.display();
    }

    return EXIT_SUCCESS;
}
