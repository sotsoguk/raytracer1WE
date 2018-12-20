#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"

class sphere: public hitable{

    public:
        sphere(){}
        sphere(vec3 center, float r): center(center), radius(r) {};
        virtual bool hit(const ray& r, float t_min, float t_max, intersect_record& rec) const;
        vec3 center;
        float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, intersect_record& rec) const{
    
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discrim = b*b - a*c;
    if (discrim > 0){
        float tmp = (-b-sqrt(b*b-a*c))/a;
        if (tmp < t_max && tmp > t_min) {
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius; // normalize normal, rec-p -center is length radius
            return true;
        }
        tmp = (-b+sqrt(b*b-a*c))/a;
        if (tmp < t_max && tmp > t_min) {
            rec.t = tmp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius; // normalize normal, rec-p -center is length radius
            return true;
        }
    }

    return false;

}
#endif
