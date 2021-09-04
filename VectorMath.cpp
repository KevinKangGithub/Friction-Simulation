#include "VectorMath.h"
#include <stack>
#include <algorithm>
#include <functional>

float VectorMath::crossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v2.y) - (v1.y * v2.x); //returns the z-coordinate of the cross product https://www.mathsisfun.com/algebra/vectors-cross-product.html
}

float VectorMath::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v1.y) + (v1.y * v2.y);
}

float VectorMath::distanceSquared(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

VectorMath::ConvexHullSolver::ConvexHullSolver(std::vector<sf::Vector2f> vertices) {
    this->topLeftPoint = sf::Vector2f(vertices.at(0).x, vertices.at(0).y);

    for (size_t i = 1; i < vertices.size(); i++) {
        if (vertices.at(i).x < topLeftPoint.x || (vertices.at(i).x == topLeftPoint.x && vertices.at(i).y < topLeftPoint.y)) {
            topLeftPoint = sf::Vector2f(vertices.at(i).x, vertices.at(i).y);
        }
    }

    this->vertices = vertices;
}

VectorMath::ConvexHullSolver::~ConvexHullSolver() {};

std::vector<sf::Vector2f> VectorMath::ConvexHullSolver::getConvexHull() {
    std::stack<sf::Vector2f> stack;
    std::sort(vertices.begin(), vertices.end(), std::bind(&VectorMath::ConvexHullSolver::compare, this, std::placeholders::_1, std::placeholders::_2));
    return std::vector<sf::Vector2f>();
}

int VectorMath::ConvexHullSolver::getOrientation(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    sf::Vector2f transformedV1 = p1 - topLeftPoint;
    sf::Vector2f transformedV2 = p2 - topLeftPoint;

    float crossProduct = VectorMath::crossProduct(transformedV2, transformedV1);
    if (crossProduct > 0) return DIRECTION_CLOCKWISE;
    else if (crossProduct < 0) return DIRECTION_COUNTERCLOCKWISE;
    return DIRECTION_COLINEAR;
    return 0;
}

bool VectorMath::ConvexHullSolver::compare(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    int orientation = VectorMath::ConvexHullSolver::getOrientation(v1, v2);

    if (orientation == DIRECTION_COUNTERCLOCKWISE) return true;
    else if (orientation == DIRECTION_CLOCKWISE) return false;
    else {
        float d1 = distanceSquared(topLeftPoint, v1);
        float d2 = distanceSquared(topLeftPoint, v2);
        if (d2 >= d1) return true;
        else return false;
    }
}

