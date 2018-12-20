#include <iostream>

#include <ray.h>

// first try in c++ after years, raytracing in a weekend..

float hit_sphere(const vec3& center, float radius, const ray& r){

    vec3 ac = r.origin() - center; // oc means ac in the book
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(ac, r.direction());
    float c = dot(ac,ac) - radius * radius;
    float discrim  = b*b - 4*a*c;
    //return (discrim > 0); // only check for intersection, not where / when
    if (discrim < 0) {
        return -1.0;
    }
    else {
        return (-b-sqrt(discrim)) / (2.0 * a);
    }
}
vec3 color(const ray& r){
    // color sphere red
    float t = hit_sphere(vec3(0,0,-1),0.5,r);
    if (t>0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t)-vec3(0,0,-1));
        return 0.5 * vec3(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);

}

int main() {
    
    // Test some ppm output
    int nx = 600;
    int ny = 300;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0, 0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);
    
    for (int j = ny-1; j >= 0; j--){
        for (int i = 0; i < nx; i++) {
            
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

}