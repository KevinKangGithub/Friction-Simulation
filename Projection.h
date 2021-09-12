#pragma once
struct Projection {
    float min;
    float max;

    bool intersects(const Projection& p);
};

