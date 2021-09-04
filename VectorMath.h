#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace VectorMath {
    float crossProduct(const sf::Vector2f &v1, const sf::Vector2f &v2);
    float dotProduct(const sf::Vector2f &v1, const sf::Vector2f &v2);
    float distanceSquared(const sf::Vector2f &v1, const sf::Vector2f &v2);
    
    class ConvexHullSolver {
    public:
        ConvexHullSolver(std::vector<sf::Vector2f> vertices);
        ~ConvexHullSolver();
        std::vector<sf::Vector2f> getConvexHull();
    private:

        static const int DIRECTION_CLOCKWISE = -1;
        static const int DIRECTION_COUNTERCLOCKWISE = 1;
        static const int DIRECTION_COLINEAR = 0;

        sf::Vector2f topLeftPoint;
        sf::Vector2f bottomRightPoint;
        std::vector<sf::Vector2f> vertices;

        int getOrientation(const sf::Vector2f &origin, const sf::Vector2f &p1, const sf::Vector2f &p2);
        bool compare(const sf::Vector2f &v1, const sf::Vector2f &v2);

    };
}
