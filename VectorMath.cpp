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
    this->vertices = vertices;

    std::sort(this->vertices.begin(), this->vertices.end(), std::bind(&VectorMath::ConvexHullSolver::compare, this, std::placeholders::_1, std::placeholders::_2));

    topLeftPoint = vertices[0];
    bottomRightPoint = vertices[vertices.size() - 1];
}

VectorMath::ConvexHullSolver::~ConvexHullSolver() {};

std::vector<sf::Vector2f> VectorMath::ConvexHullSolver::getConvexHull() {
    std::vector<sf::Vector2f> upperHull;
    std::vector<sf::Vector2f> lowerHull;

    upperHull.push_back(topLeftPoint);
    lowerHull.push_back(topLeftPoint);

    for (size_t i = 0; i < vertices.size(); i++) {
        if (i == vertices.size() - 1 || getOrientation(topLeftPoint, vertices[i], bottomRightPoint) == DIRECTION_CLOCKWISE) {
            while (upperHull.size() >= 2 && getOrientation(upperHull[upperHull.size() - 2], upperHull[upperHull.size() - 1], vertices[i]) != DIRECTION_CLOCKWISE) {
                upperHull.pop_back();
            }
            upperHull.push_back(vertices[i]);
        }
        if (i == vertices.size() - 1 || getOrientation(topLeftPoint, vertices[i], bottomRightPoint) == DIRECTION_COUNTERCLOCKWISE) {
            while (lowerHull.size() >= 2 && getOrientation(lowerHull[lowerHull.size() - 2], lowerHull[lowerHull.size() - 1], vertices[i]) != DIRECTION_COUNTERCLOCKWISE) {
                lowerHull.pop_back();
            }
            lowerHull.push_back(vertices[i]);
        }
    }

    vertices.clear();

    for (size_t i = 0; i < upperHull.size(); i++) {
        vertices.push_back(upperHull[i]);
    }
    for (size_t i = lowerHull.size() - 2; i > 0; i--) {
        vertices.push_back(lowerHull[i]);
    }

    vertices.push_back(upperHull[0]);
    return vertices;
}

int VectorMath::ConvexHullSolver::getOrientation(const sf::Vector2f& origin, const sf::Vector2f& p1, const sf::Vector2f& p2) {
    sf::Vector2f transformedV1 = p1 - origin;
    sf::Vector2f transformedV2 = p2 - origin;

    float crossProduct = VectorMath::crossProduct(transformedV2, transformedV1);
    if (crossProduct > 0) return DIRECTION_CLOCKWISE;
    else if (crossProduct < 0) return DIRECTION_COUNTERCLOCKWISE;
    return DIRECTION_COLINEAR;
}

bool VectorMath::ConvexHullSolver::compare(const sf::Vector2f &v1, const sf::Vector2f &v2) {
    return v1.x < v2.x || (v1.x == v2.x && v1.y < v2.y);
}

