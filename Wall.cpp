#include "Wall.h"
#include "VectorMath.h"
#include "Object.h"

Wall::Wall() {};

Wall::Wall(sf::FloatRect rect) {
    corners.push_back(sf::Vector2f(rect.left, rect.top));
    corners.push_back(sf::Vector2f(rect.left + rect.width, rect.top));
    corners.push_back(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
    corners.push_back(sf::Vector2f(rect.left, rect.top + rect.height));
}

Wall::~Wall() {};

bool Wall::detectObjectCollision(const Object& o) {
    std::vector<sf::Vector2f> normals = VectorMath::calcNormals(o);

    for (size_t i = 0; i < o.getPointCount() - 1; i++) {

        float o1MaxProj = std::numeric_limits<float>::lowest();
		float o1MinProj = std::numeric_limits<float>::max();
		float o2MaxProj = std::numeric_limits<float>::lowest();
		float o2MinProj = std::numeric_limits<float>::max();

        for (size_t j = 0; j < o.getPointCount(); j++) {
            sf::Vector2f transformedPoint = o.getTransform().transformPoint(o.getPoint(j)) + o.getPosition();
            float projection = VectorMath::dotProduct(normals[i], transformedPoint);
            if (projection > o1MaxProj) o1MaxProj = projection;
            else if (projection < o1MinProj) o1MinProj = projection;
        }

        for (size_t j = 0; j < 4 ; j++) {
            float projection = VectorMath::dotProduct(normals[i], corners[i]);
            if (projection > o2MaxProj) o2MaxProj = projection;
            else if (projection < o2MinProj) o2MinProj = projection;
        }

        if (o1MaxProj < o2MinProj || o1MinProj > o2MaxProj) {
            return false;
        }
    }

    return true;
}
