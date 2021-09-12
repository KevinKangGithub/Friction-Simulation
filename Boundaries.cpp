#include "Boundaries.h"
#include "VectorMath.h"
#include "Object.h"
#include "Projection.h"
#include "Constants.h"

Boundaries::Boundaries() {};
Boundaries::~Boundaries() {};

bool Boundaries::detectObjectCollision(const Object& o) {
    Projection xProj = { o.getGlobalTransformedPoint(0).x, o.getGlobalTransformedPoint(0).x };
    Projection yProj = { o.getGlobalTransformedPoint(0).y, o.getGlobalTransformedPoint(0).y };

    for (size_t i = 1; i < o.getPointCount(); i++) {
        sf::Vector2f transformedPoint = o.getGlobalTransformedPoint(i);

        if (yProj.min > transformedPoint.y) yProj.min = transformedPoint.y;
        else if (yProj.max < transformedPoint.y) yProj.max = transformedPoint.y;
        else if (xProj.min > transformedPoint.x) xProj.min = transformedPoint.x;
        else if (xProj.max < transformedPoint.x) xProj.max = transformedPoint.x;
    }

    return (xProj.min <= 0 || xProj.max >= WINDOW_WIDTH || yProj.min <= 0 || yProj.max >= WINDOW_HEIGHT);
}
