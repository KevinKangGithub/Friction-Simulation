#include "Projection.h"

bool Projection::intersects(const Projection& p) {
    return !(p.min > max || p.max < min);
}