#include <SFML/Graphics.hpp>
#include <vector>
#include "Projection.h"

class Object;

namespace VectorMath {
    const int CLOSE_ENOUGH_RADIUS_SQUARED = 36;
    float crossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
    float crossProduct(const sf::Vector2i& v1, const sf::Vector2i& v2);
    float dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2);
    float distanceSquared(const sf::Vector2f& v1, const sf::Vector2f& v2);
    int distanceSquared(const sf::Vector2i& v1, const sf::Vector2i& v2);
    sf::Vector2f normalizeVector(const sf::Vector2f & v);

    sf::Vector2f calcCentroid(sf::ConvexShape& shape);
    float calcArea(sf::ConvexShape& shape);
    std::vector<sf::Vector2f> calcNormals(const Object& o);
    Projection projectVector(const sf::Vector2f & axis, const Object& o);

    sf::Vector2f intToFloatVector(const sf::Vector2i& v);
    
    bool isCloseEnough(const sf::Vector2i& pointPos, const sf::Vector2i& mousePos);
    
    class ConvexHullSolver {

    public:
        ConvexHullSolver(std::vector<sf::Vector2i> vertices);
        ~ConvexHullSolver();
        std::vector<sf::Vector2f> getConvexHull();
    private:

        static const int DIRECTION_CLOCKWISE = -1;
        static const int DIRECTION_COUNTERCLOCKWISE = 1;
        static const int DIRECTION_COLINEAR = 0;
        static int getOrientation(const sf::Vector2i& origin, const sf::Vector2i& p1, const sf::Vector2i& p2);
        static bool compare(const sf::Vector2i& p1, const sf::Vector2i& p2);

        sf::Vector2i topLeftPoint;
        sf::Vector2i bottomRightPoint;
        std::vector<sf::Vector2i> vertices;

    };
}
