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
    TempObject test = TempObject();
    test.setInitialPos(sf::Vector2i(400, 200));
    test.addPoint(sf::Vector2i(400, 200));
    test.addPoint(sf::Vector2i(375, 375));
    test.addPoint(sf::Vector2i(1000, 900));
    test.addPoint(sf::Vector2i(400, 200));
    world.addObject(test.toObject());
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
                    std::cout<<"mousePos: { " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + " }\n";
                    std::cout<<"initialPos: { " + std::to_string(tempObject.getInitialPos().x) + ", " + std::to_string(tempObject.getInitialPos().y) + " }\n";
                    if (tempObject.getVertexCount() > 2 && tempObject.getInitialPos().x == mousePos.x && tempObject.getInitialPos().y == mousePos.y) { 
                        //TODO method to determine if the mouse is "close enough" to the first vertex position
                        //TODO method to sort points in clockwise or counterclockwise order for the centroid and mass methods 
                        //     to work correctly or make it so that you can't draw points
                        //     
                        world.addObject(tempObject.toObject());
                        tempObject = TempObject();
                    }
                }

                addingNewVertex = false;
                break;

            case sf::Event::MouseButtonPressed:
                if (tempObject.getInitialPos().x + tempObject.getInitialPos().y == 0) {
                    tempObject.addPoint(mousePos);
                    tempObject.setInitialPos(mousePos);
                }
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
