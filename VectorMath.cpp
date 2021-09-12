#include "VectorMath.h"
#include "Object.h"
#include <stack>
#include <algorithm>

float VectorMath::crossProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v2.y) - (v1.y * v2.x); //returns the z-coordinate of the cross product https://www.mathsisfun.com/algebra/vectors-cross-product.html
}

float VectorMath::crossProduct(const sf::Vector2i& v1, const sf::Vector2i& v2) {
    return static_cast<float>((v1.x * v2.y) - (v1.y * v2.x));
}

float VectorMath::dotProduct(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}

sf::Vector2f VectorMath::intToFloatVector(const sf::Vector2i& v) {
    return sf::Vector2f(static_cast<float>(v.x), static_cast<float>(v.y));
}

float VectorMath::distanceSquared(const sf::Vector2f& v1, const sf::Vector2f& v2) {
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

int VectorMath::distanceSquared(const sf::Vector2i& v1, const sf::Vector2i& v2) {
    return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
}

sf::Vector2f VectorMath::normalizeVector(const sf::Vector2f& v) {
    float a = 1 / std::sqrt(v.x * v.x + v.y * v.y);
    return sf::Vector2f(v.x * a, v.y * a);
}

bool VectorMath::isCloseEnough(const sf::Vector2i& pointPos, const sf::Vector2i& mousePos) {
    return distanceSquared(pointPos, mousePos) < CLOSE_ENOUGH_RADIUS_SQUARED;
}

sf::Vector2f VectorMath::calcCentroid(sf::ConvexShape& shape) {
    // https://en.wikipedia.org/wiki/Centroid#Of_a_polygon
    // point MUST be organized in counter-clockwise order for this to work

    float A = 1.f / (6.f * calcArea(shape));
    float Cx = 0.f;
    float Cy = 0.f;
    float xi, xi1, yi, yi1;

    for (size_t i = 0; i < shape.getPointCount() - 1; i++) {
        xi = shape.getPoint(i).x;
        xi1 = shape.getPoint(i + 1).x;
        yi = shape.getPoint(i).y;
        yi1 = shape.getPoint(i + 1).y;

        Cx += (xi + xi1) * (xi * yi1 - xi1 * yi);
        Cy += (yi + yi1) * (xi * yi1 - xi1 * yi);
    }

    return sf::Vector2f(Cx * A, Cy * A);
    return sf::Vector2f();
}

float VectorMath::calcArea(sf::ConvexShape& shape) {
    // https://en.wikipedia.org/wiki/Shoelace_formula
    // point must be organized in counter-clockwise order to get a positive result

    float totalMass = 0.f;
    size_t pointCount = shape.getPointCount();

    for (size_t i = 0; i < pointCount - 1; i++) {
        totalMass += shape.getPoint(i).x * shape.getPoint(i + 1).y;
        totalMass -= shape.getPoint(i + 1).x * shape.getPoint(i).y;
    }
    
    return (totalMass / 2);
}

std::vector<sf::Vector2f> VectorMath::calcNormals(const Object& o) { //method assumes that the last point is equal to the first point
    std::vector<sf::Vector2f> ret;
    for (size_t i = 0; i < o.getPointCount() - 1; i++) {
        sf::Vector2f edge = sf::Vector2f(o.getGlobalTransformedPoint(i) - o.getGlobalTransformedPoint(i + 1)); //get the edge formed by next point and current point

        //get the perpendicular of the edge relative to the center of the object, we can use this sane vector relative to global coordinates as an axis as its
        //direction will be unchanged when moving it to the origin
        sf::Vector2f normal(edge.y, -edge.x); 
        
        ret.push_back(VectorMath::normalizeVector(normal)); //normalize the vector to a unit vector
    }
    return ret;
}

float VectorMath::projectPoint(const sf::Vector2f& axis, const sf::Vector2f& point) {
    return VectorMath::dotProduct(axis, point);
};
Projection VectorMath::projectObject(const sf::Vector2f& axis, const Object& o) {
    sf::Vector2f transformedPoint = o.getGlobalTransformedPoint(0);
    Projection p = { VectorMath::projectPoint(axis, transformedPoint), VectorMath::projectPoint(axis, transformedPoint) };

    for (size_t i = 1; i < o.getPointCount(); i++) {
        sf::Vector2f transformedPoint = o.getGlobalTransformedPoint(i);
         float projection = VectorMath::projectPoint(axis, transformedPoint);
         if (projection < p.min) p.min = projection;
         else if (projection > p.max) p.max = projection;
    }
    return p;
}

VectorMath::ConvexHullSolver::ConvexHullSolver(std::vector<sf::Vector2i> vertices) {
    this->vertices = vertices;

    std::sort(this->vertices.begin(), this->vertices.end(), &VectorMath::ConvexHullSolver::compare);

    topLeftPoint = this->vertices[0];
    bottomRightPoint = this->vertices[this->vertices.size() - 1];
}

VectorMath::ConvexHullSolver::~ConvexHullSolver() {};

std::vector<sf::Vector2f> VectorMath::ConvexHullSolver::getConvexHull() {
    std::vector<sf::Vector2i> upperHull;
    std::vector<sf::Vector2i> lowerHull;

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

    std::vector<sf::Vector2f> returned;

    for (size_t i = 0; i < upperHull.size(); i++) {
        returned.push_back(intToFloatVector(upperHull[i]));
    }
    for (size_t i = lowerHull.size() - 2; i > 0; i--) {
        returned.push_back((sf::Vector2f) lowerHull[i]);
    }

    returned.push_back(intToFloatVector(upperHull[0]));
    return returned;
}

int VectorMath::ConvexHullSolver::getOrientation(const sf::Vector2i& origin, const sf::Vector2i& p1, const sf::Vector2i& p2) {
    sf::Vector2i transformedV1 = p1 - origin;
    sf::Vector2i transformedV2 = p2 - origin;

    float crossProduct = VectorMath::crossProduct(transformedV2, transformedV1);
    if (crossProduct > 0) return DIRECTION_CLOCKWISE;
    else if (crossProduct < 0) return DIRECTION_COUNTERCLOCKWISE;
    return DIRECTION_COLINEAR;
}

bool VectorMath::ConvexHullSolver::compare(const sf::Vector2i& v1, const sf::Vector2i& v2) {
    return v1.x < v2.x || (v1.x == v2.x && v1.y < v2.y);
}

