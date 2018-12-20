#ifndef hitablelisth
#define hitablelisth

#include "hitable.h"

class hitable_list: public hitable {
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) {list = l; list_size = n;}
        virtual bool hit(const ray&r, float t_min, float t_max, intersect_record& rec) const;
        hitable **list;
        int list_size;
};

bool hitable_list::hit(const ray&r , float t_min, float t_max, intersect_record& rec) const {
    intersect_record temp_rec;
    bool hit_any_object = false;
    double closest_t = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r,t_min,closest_t, temp_rec)){
            hit_any_object = true;
            closest_t = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_any_object;
}

#endif