#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct intersect_record{
    float t;
    vec3 p;
    vec3 normal;
};

class hitable{
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, intersect_record& rec) const = 0;
};

#endif