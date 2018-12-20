#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray
{
    public:
        ray() {}
        ray(const vec3& a, const vec3& b) { A = a; B = b;}

    vec3 origin() const     {return A;}
    vec3 direction() const  {return B;}
    vec3 point_at_parameter(float t) const { return A + t * B;}
    vec3 A;
    vec3 B;
};

vec3 random_point_in_unit_sphere(){ 
    vec3 p;
    do {
        p = 2.0 * vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    } while (dot(p,p) >= 1.0);
    return p;
}
#endif